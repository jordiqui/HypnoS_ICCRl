<p align="center">
  <img src="http://outskirts.altervista.org/forum/ext/dmzx/imageupload/img-files/2/ca292f8/8585091/34788e79c6bbe7cf7bb578c6fb4d11f8.jpg" alt="Hypnos logo">
</p>

<h1 align="center">Hypnos - Fork comunitario IJCCRL</h1>

## Aviso sobre licencia y procedencia

Este proyecto es un **fork permitido bajo la licencia GNU GPLv3** del motor Hypnos (derivado de Stockfish). El código fuente de Hypnos es libre y, de acuerdo con la licencia, cualquiera puede estudiarlo, modificarlo y redistribuirlo; por ello hemos creado esta versión mantenida por **Jorge Ruiz Centelles y Codex Open IA**. Toda la obra sigue amparada por la [GPLv3](./LICENSE), y las aportaciones que añadamos permanecerán bajo la misma licencia para respetar el espíritu de software libre.

## Propósito de esta versión

Nuestro objetivo es mantener un motor UCI sólido y transparente, documentando claramente las posibilidades de uso y las funciones avanzadas que hereda de Hypnos:

- Motor libre y fuerte para análisis y juego automatizado de ajedrez.
- Compatible con cualquier interfaz gráfica UCI (GUI); el propio motor no incluye tablero ni gestor de partidas.
- Basado en Stockfish, con divergencias estructurales y un sistema de aprendizaje personalizado heredado de Hypnos.

## Créditos y agradecimientos

- Gracias al autor y mantenedores originales de **Hypnos**, cuyo trabajo hace posible esta bifurcación.
- Reconocimiento al equipo de **Stockfish** por el motor base y su apertura a la comunidad.
- Agradecimiento a **Andrew Grant** por la plataforma [OpenBench](https://github.com/AndyGrant/OpenBench), empleada para pruebas SPRT distribuidas.

## Opciones UCI principales

A continuación se resumen las opciones más utilizadas del motor. Todas se configuran desde la GUI UCI de tu preferencia.

### Libros de apertura

- **Book1 / Book2**: habilita cada libro externo y define su ruta (`Book1 File`, `Book2 File`).
- **BestBookMove**: limita la selección al mejor movimiento del libro.
- **Depth / Width**: controlan profundidad máxima (1–350) y número de jugadas candidatas (1–10).

### Autoaprendizaje y experiencia

- **Experience file**: el motor registra posiciones y movimientos para reutilizarlos como libro de experiencia.
- **Fragmentación**: las posiciones duplicadas se consolidan en memoria para evitar datos redundantes.
- **Experience Readonly**: sólo lectura del archivo de experiencia.
- **Experience Book / Width / Eval Importance / Min Depth / Max Moves**: convierten la experiencia en libro de juego, ponderando evaluación frente a frecuencia, estableciendo profundidad mínima y límite de jugadas.

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
