# Sudoku++

![C++](https://img.shields.io/badge/C%2B%2B-20-blue?logo=cplusplus)
![Raylib](https://img.shields.io/badge/Raylib-5.5-green?logo=raylib)
![CMake](https://img.shields.io/badge/CMake-3.16+-orange?logo=cmake)
![License](https://img.shields.io/badge/License-MIT-yellow)
![Status](https://img.shields.io/badge/Status-In%20Progress-red)

A desktop Sudoku game built from scratch in **C++20** with a graphical interface powered by **Raylib**. Generates solvable, unique Sudoku puzzles with four difficulty levels — from easy to expert.

---

## Screenshot

> **TODO:** 
>
> ```
> ![Gameplay](docs/screenshot.png)
> ```

---

## Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Built With](#built-with)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Running](#running)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Roadmap](#roadmap)
- [License](#license)
- [Contact](#contact)

---

## About the Project

This project was born out of a desire to combine algorithmic problem-solving with graphical programming. The goal was to build a **complete Sudoku game** — not just a solver, but a full pipeline that:

1. **Generates** a valid, fully-filled 9×9 Sudoku grid.
2. **Shuffles** the board using row/column/band permutations to create variety.
3. **Removes cells** according to a chosen difficulty profile while ensuring the puzzle has **exactly one unique solution**.
4. **Presents** the puzzle in an interactive GUI where the player can select cells, enter numbers, and get real-time feedback.

It's a great exercise in backtracking algorithms, constraint satisfaction, and rendering with a lightweight C library.

---

## Features

- Interactive GUI built with Raylib
- Four difficulty levels: **Easy**, **Medium**, **Hard**, **Expert**
- Backtracking solver that guarantees a unique solution
- Board shuffling for maximum puzzle variety
- Real-time error checking and score tracking
- Built-in timer
- Mouse + keyboard input

---

## Built With

| Technology | Purpose |
| --- | --- |
| **C++20** | Core language |
| **Raylib 5.5** | 2D graphics & input handling |
| **CMake 3.16+** | Build system |
| **FetchContent** | Automatic Raylib dependency download |

---

## Getting Started

### Prerequisites

- A C++20-compatible compiler (GCC 10+, Clang 12+, or MSVC 2019+)
- CMake **3.16** or newer
- Git
- On Linux you may need additional packages for Raylib:

  ```bash
  # Debian / Ubuntu
  sudo apt install libgl1-mesa-dev libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev
  ```

### Installation

```bash
# 1. Clone the repository
git clone https://github.com/himusuwu/SudokuSolver.git
cd SudokuSolver

# 2. Create a build directory and configure
mkdir -p build && cd build
cmake ..

# 3. Build the project
make -j$(nproc)        # Linux / macOS
# or: cmake --build .  # cross-platform alternative
```

> **Note:** Raylib is fetched automatically by CMake during the configure step — no manual installation needed.

### Running

```bash
# From the build/ directory:
make run
# or run the binary directly:
./SudokuSolver
```

---

## Project Structure

```
SudokuSolver/
├── CMakeLists.txt              # Build configuration
├── include/
│   ├── Config.hpp              # Difficulty levels & profiles
│   ├── random_gen.hpp          # Random number generation
│   ├── shuffle_board.hpp       # Board shuffling logic
│   ├── sudoku_generator.hpp    # Puzzle generation (cell removal)
│   ├── sudoku_grid.hpp         # Base grid creation
│   ├── sudoku_solver.hpp       # Backtracking solver & uniqueness check
│   └── gui/
│       └── game.hpp            # Main game loop & rendering
├── src/
│   ├── main.cpp                # Entry point
│   ├── random_gen.cpp
│   ├── shuffle_board.cpp
│   ├── sudoku_generator.cpp
│   ├── sudoku_grid.cpp
│   ├── sudoku_solver.cpp
│   └── gui/
│       └── game.cpp            # GUI implementation
└── build/                      # Build artifacts (generated)
```

---

## How It Works

```
Grid → Shuffle → Generate (remove cells) → Solve (verify uniqueness) → GUI
```

1. **`Grid`** — creates a valid base 9×9 Sudoku board.
2. **`Shuffler`** — randomly permutes rows, columns, and bands to diversify the board.
3. **`Generate`** — removes cells based on the selected `DifficultyProfile` (min/max empty cells, symmetry, solver attempts).
4. **`Solver`** — uses backtracking to verify the puzzle has exactly one solution (`check_unique`).
5. **`Game`** — renders the board via Raylib, handles user input, tracks errors, score, and time.

---

## Roadmap

- [x] Base Sudoku grid generation
- [x] Board shuffling (rows, columns, bands)
- [x] Backtracking solver
- [x] Unique-solution verification
- [x] Difficulty levels (Easy / Medium / Hard / Expert)
- [x] Interactive GUI with Raylib
- [x] Cell selection (mouse + keyboard)
- [x] Real-time error checking
- [x] Score & timer
- [ ] Pencil marks (notes in cells)
- [ ] Undo / Redo
- [ ] Hint system
- [ ] Save & load game state
- [ ] Animations & visual polish
- [ ] Sound effects
- [ ] High-score leaderboard

---

## License

Distributed under the **MIT License**. See `LICENSE` for more information.

---

## Contact

**Himus** — [GitHub Profile](https://github.com/himusuwu)

Project Link: [https://github.com/himusuwu/SudokuPlusPlus](https://github.com/himusuwu/SudokuPlusPlus)