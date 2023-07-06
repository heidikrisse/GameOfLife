# GameOfLife

A simple implementation of Conway's Game of Life game. 

## How to play

The game starts with an empty game board. You have the following options:

1. Use the default demo game board size.
2. Specify the game board size.

Once the game board is initialized, you can choose one of the following options:

- Play: The game will continuously evolve the game board until you choose to stop.
- Pause: Pause the game at the current generation.
- Step: The game will evolve the game board one generation at a time.
- : Exit the game.

## Dependencies

- Raylib

To install Raylib ... 

## Build Project

1. Navigate to the project root directory

2. Create a build directory and navigate to it:

```shell
mkdir build
cd build
```

3. Run CMake and build the project:

```shell
cmake ..
make
```

## Run Project

```shell
./GameOfLife
```

## Run Unit Tests

```shell
../tests/unit_tests_results
```
