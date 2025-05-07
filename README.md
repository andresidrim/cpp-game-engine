# Raylib PS1 Game Engine

A modular, minimalistic 3D game engine written in **C++**, built with [Raylib](https://www.raylib.com/), aiming to replicate the visual style and technical constraints of **PlayStation 1-era** games.

## 🎯 Goals

- Simple and fast architecture using low-level **C++**
- Retro aesthetics: **low poly**, **low resolution**, and affine-like rendering
- Lightweight **ECS-like architecture** (Entity-Component-System)
- Modular systems: movement, rendering, collisions, interactions, etc.
- Designed for learning, experimentation, and nostalgic 3D game prototyping

---

## 🛠 Requirements

- [MSYS2 + MinGW 64-bit](https://www.msys2.org/)
- Raylib installed via pacman:
  ```bash
  pacman -S mingw-w64-x86_64-raylib
  ```
- CMake 3.10+
- C++ compiler (MinGW or MSVC)

---

## 🔧 Build Instructions

### Windows (PowerShell)

```powershell
./build.ps1
```

### Manual Build with CMake

```bash
cmake -B build
cmake --build build
```

---

## 📁 Project Structure

```
.
├── include/
│   ├── core/         # Entity, EntityManager
│   ├── components/   # Transform, Collider, Renderable
│   ├── systems/      # MovementSystem, RenderSystem, etc.
│   ├── triggers/     # Trigger logic and events
│   └── game.hpp      # Game loop and entry point
├── src/              # Source files (.cpp)
├── build.ps1         # Windows build script
├── CMakeLists.txt
└── README.md
```

---

## 🎮 Controls

- `WASD`: Move the player
- `E`: Interact with objects (via trigger components)

---

## 🧩 Core Components & Systems

| Component   | Description                           |
|-------------|---------------------------------------|
| Transform   | Position, velocity, movement handling |
| Collider    | Bounding box for collision/triggers   |
| Renderable  | 3D cube rendering with Raylib         |

| System          | Responsibility                            |
|-----------------|--------------------------------------------|
| MovementSystem  | Handles input and player movement          |
| CollisionSystem | AABB collision detection between entities  |
| RenderSystem    | Renders entities using Raylib              |
| TriggerSystem   | Manages trigger-based interactions         |
| UIMessageSystem | Displays in-game text messages             |

---

## 🚀 Built With

- 💻 [C++](https://en.wikipedia.org/wiki/C%2B%2B)
- 🎮 [Raylib](https://www.raylib.com/)
- ⚙️ [CMake](https://cmake.org/)
- 🧰 Optional: [MSYS2](https://www.msys2.org/) + MinGW

---

## 📌 Notes

- This engine is a **work in progress**, developed in my free time as a personal learning project.
- It is not intended for commercial use.
- Final name to be decided later.
- Open-source and free to use for learning, tinkering, or building nostalgic 3D games.

---

## 📜 License

This project is licensed under the MIT License.
