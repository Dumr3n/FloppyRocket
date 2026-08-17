# Floppy Rocket

An arcade flying game built in modern C++ with the Hazel engine. Guide a tiny rocket through an endless field of shifting obstacles, manage its momentum with short thruster bursts, and chase a higher score on every run.

<p align="center">
  <img width="900" alt="Floppy Rocket gameplay" src="https://github.com/user-attachments/assets/4a5565ad-5019-43ef-b504-ff303c3f4d66" />
</p>

## Highlights

- Responsive, delta-time-based rocket physics
- Endless procedural obstacle generation
- Animated exhaust and smoke particle effects
- Colour-cycling hazards and a layered space backdrop
- Clear menu, score HUD, and game-over presentation
- Unit-tested gameplay mathematics with GoogleTest
- Automated Windows builds and tests through GitHub Actions

## Controls

| Action | Control |
| --- | --- |
| Start or restart | Left mouse button |
| Fire thruster | Hold `Space` |

## Build from source

### Requirements

- Windows 10 or later
- Visual Studio 2022 with the **Desktop development with C++** workload
- CMake 3.20 or newer
- Git

```powershell
git clone <repository-url>
cd FloppyRocket
cmake -S . -B build -A x64
cmake --build build --config Release --parallel
```

Run the game from `bin/Release-windows-x64/Sandbox/`. Game assets are copied beside the executable automatically.

## Run the tests

GoogleTest is downloaded by CMake when testing is enabled.

```powershell
cmake -S . -B build -A x64 -DBUILD_TESTING=ON
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
```

Tests cover collision geometry, HSV colour conversion, scoring, and rocket rotation constraints. The same sequence runs for every push and pull request in GitHub Actions.

## Project layout

```text
FloppyRocket/
|-- Hazel/          # Engine code
|-- Sandbox/        # Game source and assets
|-- tests/          # GoogleTest suite
```

`GameLayer` coordinates application state and presentation. `Level` owns procedural hazards and collision checks, `Player` handles motion and input, and `ParticleSystem` renders rocket effects. Renderer-independent calculations live in `GameMath`, keeping important gameplay rules straightforward to test.

## Screenshots

<p align="center">
  <img width="49%" alt="Floppy Rocket obstacle course" src="https://github.com/user-attachments/assets/820aaf07-e4f2-4052-b2fe-d94ea146ac42" />
  <img width="49%" alt="Floppy Rocket gameplay" src="https://github.com/user-attachments/assets/4a5565ad-5019-43ef-b504-ff303c3f4d66" />
</p>

## Acknowledgements

The game is built on the included [Hazel](https://github.com/TheCherno/Hazel) engine architecture and uses OpenGL, GLFW, Dear ImGui, GLM, and GoogleTest.
