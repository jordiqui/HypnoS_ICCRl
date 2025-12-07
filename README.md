<p align="center">
  <img src="./LOGO/hypnos_saturno.svg" alt="Hypnos logo inspired by Goya's Saturn" width="320">
</p>

<h1 align="center">Hypnos - IJCCRL Community Fork</h1>

Hypnos is a Stockfish-derived UCI chess engine with IJCCRL customisations. This community fork is maintained by **Jorge Ruiz Centelles and Codex Open IA**, keeping the code open and traceable for engine testers and chess enthusiasts.

## About

- Project site: <https://ijccrl.com/>
- License: [GNU GPLv3](./LICENSE). Hypnos is free software; you may study, modify, and redistribute it as long as the license is preserved.

## Purpose of this fork

We aim to keep a strong and transparent UCI engine while documenting the unique features inherited from Hypnos:

- Competitive analysis strength suitable for automated play and tournament testing.
- Compatible with any UCI graphical interface (the engine itself does not include a board or game manager).
- Structural deviations from Stockfish plus a personalised learning system derived from Hypnos.

## Core UCI options

A quick overview of the most relevant settings (configure them through your preferred UCI GUI):

- **Book1 / Book2**: enable external opening books and set their paths (`Book1 File`, `Book2 File`).
- **BestBookMove**: restricts the choice to the strongest book move.
- **Depth / Width**: maximum search depth (1–350) and number of candidate moves (1–10).
- **Experience file**: records positions and moves for reuse as an experience book; supports de-duplication and read-only mode.
- **Tactical Mode**: aggressive search profile with fewer prunings—expect higher node counts and a tactical bias.
- **Variety / Variety Max Score / Variety Max Moves**: adds controlled randomness in balanced positions with evaluation and move-count limits.
- **Random Open Mode**: probabilistic selection among strong opening moves; configure with `Random Open Plies`, `Random Open MultiPV`, `Random Open DeltaCp`, `Random Open SoftmaxT`, and `Random Seed` for reproducibility.
- **NNUE Dynamic Weights**: blends wMat/wPos depending on game phase and positional complexity.
- **NNUE ManualWeights**: override the dynamic mode with manual weights via `NNUE StrategyMaterialWeight` and `NNUE StrategyPositionalWeight`.
- **(Debug) NNUE Log Weights**: logs the weight parameters used at the search root.

## How to use the engine

1. Download or compile the binary and load it into your favourite UCI GUI.
2. Toggle the options above according to your scenario: deep analysis, self-learning, or friendly games.
3. For reproducible testing, set a non-zero `Random Seed`.

## Improvements documented in this fork

- Rewritten documentation in English with clear licensing and project provenance.
- Explicit acknowledgements to the original Hypnos author, the Stockfish project, and Andrew Grant's [OpenBench](https://github.com/AndyGrant/OpenBench) used for distributed SPRT testing.
- Consolidated summary of UCI options and their goals.

 codex/fix-code-errors-and-update-principal-page-d3j84w
### Modos de búsqueda

- **Tactical Mode**: perfil agresivo con menos podas para resolver táctica; aumenta el número de nodos y no se recomienda para controles largos.
- **Variety / Variety Max Score / Variety Max Moves**: introduce aleatoriedad controlada en posiciones equilibradas, acotando margen de evaluación y número de jugadas.
- **Random Open Mode**: variedad en aperturas mediante selección probabilística entre mejores movimientos. Configurable con `Random Open Plies`, `Random Open MultiPV`, `Random Open DeltaCp`, `Random Open SoftmaxT` y `Random Seed` para reproducibilidad.

### Control de red NNUE

- **NNUE Dynamic Weights**: combina pesos wMat/wPos según la fase de la partida y la complejidad posicional.
- **NNUE ManualWeights**: anula el modo dinámico y fija manualmente los pesos con `NNUE StrategyMaterialWeight` y `NNUE StrategyPositionalWeight`.
- **(Debug) NNUE Log Weights**: registra los parámetros usados en la raíz de la búsqueda.

## Cómo usar el motor

1. Descarga o compila el binario y cárgalo en tu GUI UCI favorita.
2. Activa o desactiva las opciones anteriores según tu escenario: análisis, autoaprendizaje o partidas amistosas.
3. Para reproducibilidad en pruebas, define un `Random Seed` mayor que cero.

## Red NNUE predeterminada

- El motor usa como red principal ("big NNUE") la **nn-2962dca31855.nnue**, que
  debe mantenerse salvo que Stockfish publique una versión oficial más
  reciente. Ajusta `EvalFile` si necesitas cargarla desde otra ruta, pero no
  cambies el nombre de referencia.
- La red compacta **nn-37f18f62d772.nnue** sigue siendo la opción secundaria
  para dispositivos con menos memoria. Puedes alternar entre ambas con la
  opción `Use Small Network` en la GUI o deshabilitando `Use_NNUE` si fuera
  necesario.
- Por política del repositorio no se distribuyen binarios: descarga ambas
  redes con `make net` o ejecutando `./scripts/net.sh`. El script verifica el
  hash esperado y solo mantiene las redes válidas en tu carpeta de trabajo.
- Las redes no se incrustan en el binario; el motor las carga desde disco
  mediante la opción `EvalFile` o las rutas por defecto en el directorio de
  trabajo.

## Mejoras realizadas en esta bifurcación

- Documentación reescrita en español, aclarando la licencia GPL y el origen como fork comunitario.
- Agradecimientos explícitos al autor de Hypnos y a los proyectos base.
- Resumen consolidado de las opciones UCI y su propósito.
- Ajustes de mantenimiento: correcciones en el sistema de construcción, selección aleatoria segura en la política de aperturas y alineación de las redes NNUE por defecto con la principal de Stockfish.

Seguiremos añadiendo y documentando nuevas mejoras en cuanto estén listas.
=======
We will continue to add and document improvements as they become available.
master
