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
- **NNUE ManualWeights**: override the dynamic mode with manual weights via `NNUE StrategyMaterialWeight` and `NNUE StrategyPositionalWeight` (both default to 0 with range [-12, 12]).
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
- **NNUE ManualWeights**: anula el modo dinámico y fija manualmente los pesos con `NNUE StrategyMaterialWeight` y `NNUE StrategyPositionalWeight` (ambos con valor predeterminado 0 y rango [-12, 12]).
- **(Debug) NNUE Log Weights**: registra los parámetros usados en la raíz de la búsqueda.

## Settings

Recomendaciones rápidas para los controles más habituales. Ajusta los valores en tu GUI UCI siguiendo cada perfil de tiempo:

| Opción clave | Bullet (1+0 / 2+1) | Blitz (3+2 / 5+3) | Classical (120+15) |
| --- | --- | --- | --- |
| **Depth / Width** | Depth 24–28, Width 2 | Depth 30–34, Width 3–4 | Depth 36–42, Width 5–6 |
| **Tactical Mode** | Activado para encontrar tácticas rápidas | Activado solo en posiciones complejas | Desactivado para evitar consumo extra |
| **Variety / Max Score / Max Moves** | Variety 20, Max Score 15, Max Moves 4 para evitar repetición | Variety 10, Max Score 10, Max Moves 3 | Variety 0 (determinista) |
| **Random Open Mode** (`Random Open Plies / MultiPV / DeltaCp / SoftmaxT`) | 6 / 3 / 25 / 120 para mezclar aperturas | 4 / 2 / 20 / 80 | 0 / 1 / 0 / 0 (juego sólido) |
| **Experience file** | Activado, tamaño pequeño (p. ej. 64–128 MB) | Activado, tamaño medio (256–512 MB) | Activado, tamaño amplio (1024 MB+) |
| **Book1 / Book2** | Book1 ligero con `BestBookMove` desactivado | Book1 sólido y Book2 opcional, `BestBookMove` activado | Libros completos, `BestBookMove` activado |
| **NNUE Dynamic Weights** | Activado | Activado | Activado |
| **NNUE StrategyMaterialWeight / PositionalWeight** | 0 / 0 (predeterminado) | +4 / +2 para equilibrar | +8 / +6 para partidas largas |
| **Random Seed** | Valor fijo para reproducibilidad de tests | Valor fijo | Valor fijo |

## Cómo usar el motor

1. Descarga o compila el binario y cárgalo en tu GUI UCI favorita.
2. Activa o desactiva las opciones anteriores según tu escenario: análisis, autoaprendizaje o partidas amistosas.
3. Para reproducibilidad en pruebas, define un `Random Seed` mayor que cero.

## Red NNUE predeterminada

- El motor empaqueta por defecto la red principal ("big NNUE") **nn-2962dca31855.nnue**
  y la red compacta **nn-37f18f62d772.nnue** dentro del binario, siguiendo el
  mismo flujo de trabajo que en nuestros proyectos Revolution y Deepalienist.
  Las redes se descargan automáticamente al compilar (`make` invoca el objetivo
  `net` que valida los hashes) y quedan accesibles sin necesidad de ficheros
  externos al ejecutar el motor.
- Puedes alternar entre ambas redes con la opción `Use Small Network` o
  desactivar la evaluación NNUE con `Use_NNUE`; `EvalFile` sigue permitiendo
  cargar manualmente una red diferente si necesitas pruebas específicas.

### Cómo usar las redes NNUE integradas

- Al estar incrustadas, no es necesario copiar las redes junto al ejecutable;
  el binario resultante incorpora los pesos y está listo para ejecutarse en
  cualquier carpeta.
- Si deseas mantener un ejecutable más ligero, compila con
  `CXXFLAGS+=' -DNNUE_EMBEDDING_OFF'` para volver al modo de carga desde disco.
- Usa `make net` o `./scripts/net.sh` para refrescar los ficheros `.nnue` que
  se van a incrustar; el `Makefile` descargará automáticamente las redes si no
  están presentes al iniciar la compilación.

## Mejoras realizadas en esta bifurcación

- Documentación reescrita en español, aclarando la licencia GPL y el origen como fork comunitario.
- Agradecimientos explícitos al autor de Hypnos y a los proyectos base.
- Resumen consolidado de las opciones UCI y su propósito.
- Ajustes de mantenimiento: correcciones en el sistema de construcción, selección aleatoria segura en la política de aperturas y alineación de las redes NNUE por defecto con la principal de Stockfish.

Seguiremos añadiendo y documentando nuevas mejoras en cuanto estén listas.
