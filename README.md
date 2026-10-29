# Poople Solver

## Build

Requirements: CMake 3.16 or newer and a C++17-compatible compiler.

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/poople_solver
```

Enter a four-letter dictionary word when prompted. Enter `q` to quit.

After a route is shown, enter any route word that the game rejects. The solver
permanently removes it from `db/dictionary.txt` and immediately refits a route
without that word. Press Enter to choose a new start word.
