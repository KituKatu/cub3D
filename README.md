*This project has been created as part of the 42 curriculum by <adecheri>, <jmcgrane>*

## Description

**cub3D** is a 42 school project inspired by the world's first FPS game, *Wolfenstein 3D* (1992). The goal is to build a realistic 3D maze renderer from scratch in C using the **raycasting** technique — projecting a 2D grid map into a first-person 3D perspective without any 3D engine.

The project takes a `.cub` scene description file as input, which defines:
- Texture paths for the four cardinal wall directions (North, South, East, West)
- Floor and ceiling RGB colours
- The map layout, composed of walls (`1`), open spaces (`0`), and a player starting position/orientation (`N`, `S`, `E`, `W`)

Key features implemented:
- Custom `.cub` map parser with validation and flood-fill closed-map checking
- Digital Differential Analysis (DDA) raycasting for wall rendering
- Textured walls with correct perspective-corrected distance shading
- First-person player movement and rotation (keyboard + mouse)
- Minimap overlay
- MLX42 graphics library (OpenGL-backed, GLFW)

---

## Instructions

### Dependencies

Before building, ensure the following are installed on your system:

- `gcc` or `cc`
- `cmake` (≥ 3.18)
- `GLFW3` development libraries

On Debian/Ubuntu:
```bash
sudo apt-get update
sudo apt-get install cmake libglfw3-dev
```

On Arch Linux:
```bash
sudo pacman -S cmake glfw-x11
```

### Compilation

Clone the repository (including submodules) and build:

```bash
git clone --recurse-submodules <repo-url>
cd cub3d
make
```

`make` will automatically initialise the MLX42 submodule, run `cmake` to build it, and then compile the project. The binary `cub3D` will appear in the root directory.

Other Makefile targets:

| Target    | Effect                                      |
|-----------|---------------------------------------------|
| `make`    | Build `cub3D`                               |
| `make re` | Full clean rebuild                          |
| `make clean` | Remove object files and MLX42 build artefacts |
| `make fclean` | Remove all compiled outputs              |

### Execution

```bash
./cub3D <path-to-map>.cub
```

Map files must be placed in the `maps/` directory. Example:

```bash
./cub3D maps/map_1.cub
```

### Controls

| Key / Input       | Action              |
|-------------------|---------------------|
| `W A S D`         | Move player         |
| `←` / `→` arrows  | Rotate view        |
| Mouse movement    | Rotate view         |
| `ESC`             | Quit                |

---

## Resources

### Raycasting & Maths

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the primary reference for DDA raycasting, fisheye correction, texture mapping, and sprite rendering.
- [RayCasting Tutorial Wiki (vinibiavatti1)](https://github.com/vinibiavatti1/RayCastingTutorial/wiki/RayCasting) — supplementary diagrams and pseudocode for understanding the geometry.
- [Wolfenstein 3D's Game Engine (Fabien Sanglard)](https://fabiensanglard.net/wolfenstein3d/) — in-depth breakdown of the original raycaster this project is based on.

### MLX42 / Graphics

- [MLX42 Documentation](https://github.com/codam-coding-college/MLX42) — official repository and API reference for the graphics library used in this project.

### Map Format / 42 Project

- The subject PDF for cub3D (available on the 42 intranet) specifies the exact `.cub` scene description format and mandatory/bonus requirements.

---

### AI Usage

GitHub Copilot (Claude Sonnet) was used during this project in the following ways:

- **Debugging**: Identifying logic errors in the map parser and raycasting pipeline (e.g., inverted return-value checks, redundant function calls, premature null-pointer dereferences).
- **Code review**: Spot-checking individual functions for off-by-one errors, memory leaks, and undefined behaviour.

AI was **not** used to generate core algorithmic code (raycasting, DDA, texture mapping) — those were implemented by hand, guided by the references above.
