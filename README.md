# ChromaWeave: A 2D Color-Based Puzzle-Strategy Game

## Overview
ChromaWeave is a unique 2D puzzle-strategy game built in C++ using the SFML library. Players weave colored threads across a grid to match target patterns while countering disruptive anomalies that alter the grid. The game blends strategic planning with dynamic puzzle-solving, offering a fresh experience distinct from traditional puzzle or strategy games.

This open-source project is designed for developers, gamers, and educators interested in C++ game development, pattern-matching mechanics, and dynamic systems. By sponsoring ChromaWeave via GitHub Sponsors, you support new features, level designs, and educational resources for the community.

## Features
- **Color Thread Mechanics**: Weave red, green, and blue threads to match target patterns.
- **Dynamic Anomalies**: Counter grid-altering anomalies to maintain control.
- **Minimalist Visuals**: Clean 2D graphics with vibrant color effects.
- **Cross-Platform**: Runs on Windows, macOS, and Linux via SFML.
- **Modular Codebase**: Well-structured C++ code for easy extension and learning.

## Getting Started

### Prerequisites
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support.
- **SFML Library**: Version 2.5.1 or later (install via [SFML's official site](https://www.sfml-dev.org/) or package manager).
- **CMake**: Version 3.10 or later for building.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/chromaweave.git
   cd chromaweave
   ```
2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
3. Configure with CMake:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   cmake --build .
   ```
5. Run the game:
   ```bash
   ./ChromaWeave
   ```

## Gameplay
- **Objective**: Match the target pattern by weaving colored threads while keeping anomaly disruption below the threshold.
- **Controls**:
  - **Arrow Keys**: Move the cursor on the grid.
  - **R/G/B**: Place red, green, or blue threads.
  - **Space**: Counter an anomaly at the cursor.
  - **Enter**: Submit the pattern for scoring.
  - **Ctrl+R**: Reset the level.
  - **Esc**: Pause or exit.
- **Mechanics**: Threads connect grid points to form patterns. Anomalies randomly alter threads, increasing disruption. Counter anomalies strategically to maintain control.

## Project Structure
- `src/main.cpp`: Game entry point and main loop.
- `src/Entity.hpp`: Base class for game entities (threads, anomalies).
- `src/Game.hpp`: Core game logic, pattern matching, and rendering.
- `assets/`: Placeholder for textures/fonts (add your own or use SFML defaults).

## Contributing
Contributions are welcome! Fork the repo, create a feature branch, and submit a pull request. For major changes, open an issue to discuss your ideas.

## Sponsorship
Support ChromaWeave’s development through [GitHub Sponsors](https://github.com/sponsors/raziyagavrilov)! Your contributions fund:
- New pattern designs and anomaly types.
- Enhanced thread mechanics and visual effects.
- Tutorials for C++ and game development.
- Optimizations for broader platform support.

## License
Licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.org/) for graphics and input.
- Inspired by color-based puzzles and dynamic strategy games.
- Thanks to the open-source community for feedback and inspiration.

---

**Sponsor ChromaWeave to weave vibrant new puzzle experiences!**
