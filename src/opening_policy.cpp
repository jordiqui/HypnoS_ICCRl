/*
  HypnoS, a UCI chess playing engine derived from Stockfish
  Copyright (C) 2004-2025 The Stockfish developers (see AUTHORS file)

  HypnoS is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  HypnoS is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "opening_policy.h"

#include <array>
#include <deque>
#include <ctime>
#include <initializer_list>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <mutex>

#include "misc.h"
#include "movegen.h"
#include "position.h"
#include "uci.h"

namespace Hypnos {

namespace {

constexpr auto StartFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

struct PolicyMove {
    Move move{ Move::none() };
    int  weight{ 0 };
};

using PolicyTable = std::unordered_map<Key, std::vector<PolicyMove>>;

PolicyTable policyTable;
std::once_flag policyInit;
PRNG         policyRng((uint64_t)time(nullptr));

Move find_move(const Position& pos, std::string_view uciMove) {
    for (const auto m : MoveList<LEGAL>(pos))
        if (UCIEngine::move(m, pos.is_chess960()) == uciMove)
            return m;

    return Move::none();
}

bool apply_line(Position& pos, std::deque<StateInfo>& states, const std::vector<std::string>& moves) {
    for (const auto& mstr : moves)
    {
        const Move m = find_move(pos, mstr);
        if (m == Move::none())
            return false;

        states.emplace_back();
        pos.do_move(m, states.back());
    }

    return true;
}

void add_policy(const std::vector<std::string>& path,
                std::initializer_list<std::pair<std::string, int>> responses) {
    StateListPtr states = std::make_unique<std::deque<StateInfo>>(1);
    Position     pos;
    pos.set(StartFEN, false, &states->back());

    if (!apply_line(pos, *states, path))
        return;

    std::vector<PolicyMove> entries;
    entries.reserve(responses.size());

    for (const auto& [uciMove, weight] : responses)
    {
        const Move m = find_move(pos, uciMove);
        if (m != Move::none() && weight > 0)
            entries.push_back({ m, weight });
    }

    if (!entries.empty())
        policyTable[pos.key()] = std::move(entries);
}

void init_table() {
    // 1.e4 responses: dynamic Sicilian priority with French as solid alternative
    add_policy({ "e2e4" },
               {
                   { "c7c5", 70 },  // Sicilian counterattack
                   { "e7e6", 30 },  // French solidity
               });

    // 1.e4 c5 2.Nf3: prefer active Najdorf/Classical setups
    add_policy({ "e2e4", "c7c5", "g1f3" },
               {
                   { "d7d6", 60 },
                   { "e7e6", 40 },
               });

    // 1.e4 c5 2.Nf3 d6 3.d4: capture toward open Sicilian structures
    add_policy({ "e2e4", "c7c5", "g1f3", "d7d6", "d2d4" },
               {
                   { "c5d4", 80 },
                   { "g8f6", 20 },
               });

    // 1.e4 e6 2.d4 d5 3.e5: favor counterplay with ...c5 and ...f6 in French Advance
    add_policy({ "e2e4", "e7e6", "d2d4", "d7d5", "e4e5" },
               {
                   { "c7c5", 60 },
                   { "f7f6", 40 },
               });

    // 1.d4 repertoire
    add_policy({ "d2d4" },
               {
                   { "d7d5", 60 },   // Solid Slav/QGD starting move
                   { "g8f6", 40 },   // Flexible Indian setups
               });

    // 1.d4 Nf6 2.c4 e6 3.Nf3: Queens Indian and dynamic ...c5
    add_policy({ "d2d4", "g8f6", "c2c4", "e7e6", "g1f3" },
               {
                   { "b7b6", 70 },  // QID
                   { "c7c5", 30 },  // Benoni-style strike when sound
               });

    // 1.d4 Nf6 2.c4 e6 3.Nc3: similar plan with pressure on light squares
    add_policy({ "d2d4", "g8f6", "c2c4", "e7e6", "b1c3" },
               {
                   { "b7b6", 60 },
                   { "c7c5", 40 },
               });

    // 1.d4 d5 2.c4: Slav/Orthodox with dynamic counter ...c5/...e5 where viable
    add_policy({ "d2d4", "d7d5", "c2c4" },
               {
                   { "c7c6", 55 },  // Slav
                   { "e7e6", 45 },  // Orthodox QGD aiming for ...c5 or ...e5
               });

    // 1.d4 d5 2.c4 c6 3.Nc3 Nf6 4.Nf3: encourage ...c5 to challenge the center
    add_policy({ "d2d4", "d7d5", "c2c4", "c7c6", "b1c3", "g8f6", "g1f3" },
               {
                   { "c6c5", 70 },
                   { "e7e6", 30 },
               });

    // 1.d4 d5 2.c4 e6 3.Nc3: early ...c5 pressure in QGD structures
    add_policy({ "d2d4", "d7d5", "c2c4", "e7e6", "b1c3" },
               {
                   { "c7c5", 65 },
                   { "g8f6", 35 },
               });
}

}  // namespace

namespace OpeningPolicy {

void init() { std::call_once(policyInit, init_table); }

Move probe(const Position& pos) {
    init();

    const auto it = policyTable.find(pos.key());
    if (it == policyTable.end())
        return Move::none();

    const auto& entries = it->second;
    int         total   = 0;

    for (const auto& e : entries)
        total += e.weight;

    if (total <= 0)
        return Move::none();

    int pick = static_cast<int>(policyRng.rand<unsigned>() % total);
    for (const auto& e : entries)
    {
        pick -= e.weight;
        if (pick < 0)
        {
            // Validate move legality at probe time in case the position changed
            for (const auto m : MoveList<LEGAL>(pos))
                if (m == e.move)
                    return m;

            break;
        }
    }

    return Move::none();
}

}  // namespace OpeningPolicy

}  // namespace Hypnos

