# Caveland

Caveland is a C++/SFML platformer built around a custom object-oriented game architecture.
The project contains 21 game classes and implements game states, level loading, collisions,
combat, projectiles, menus, transitions, animation, and several enemy types.

## Tech

- C++20
- SFML 2.x
- CMake

## Build

Install SFML 2.x and make it discoverable by CMake, then run:

```bash
cmake -S . -B build
cmake --build build
```

The game loads resources through relative paths (`image/`, `sound/`, `font/`, `level/`,
`game_data/`), so run the executable with the repository root as the working directory.
