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

#ifndef OPENING_POLICY_H_INCLUDED
#define OPENING_POLICY_H_INCLUDED

#include "types.h"

namespace Hypnos {

class Position;
class Move;

namespace OpeningPolicy {

// Initialize the built-in policy book.
void init();

// Probe the policy book for a move in the given position. Returns Move::none()
// if the position is not covered or if no legal move matches the policy entry.
Move probe(const Position& pos);

}  // namespace OpeningPolicy

}  // namespace Hypnos

#endif  // #ifndef OPENING_POLICY_H_INCLUDED
