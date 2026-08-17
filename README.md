# Floppy Rocket

[![CI](https://github.com/Dumr3n/FloppyRocket/actions/workflows/ci.yml/badge.svg)](https://github.com/Dumr3n/FloppyRocket/actions/workflows/ci.yml)
[![Latest release](https://img.shields.io/github/v/release/Dumr3n/FloppyRocket?display_name=tag&sort=semver)](https://github.com/Dumr3n/FloppyRocket/releases/latest)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/build-CMake-064F8C?logo=cmake)](https://cmake.org/)
[![Tests](https://img.shields.io/badge/tests-GoogleTest-34A853?logo=google)](https://google.github.io/googletest/)
[![Platform](https://img.shields.io/badge/platform-Windows-0078D4?logo=windows)](https://github.com/Dumr3n/FloppyRocket/releases/latest)

An arcade flying game built in modern C++ with the Hazel engine. Guide a tiny rocket through an endless field of shifting obstacles, manage its momentum with short thruster bursts, and chase a higher score on every run.

<p align="center">
  <img width="900" alt="Floppy Rocket gameplay" src="https://github.com/user-attachments/assets/7bed4d75-1b92-4de9-80d2-084e6dd02267" />
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

## Download and play

Download **FloppyRocket-Windows-x64.zip** from the [latest release](https://github.com/Dumr3n/FloppyRocket/releases/latest), extract it, and run `FloppyRocket.exe`. Keep the `Resources` directory beside the executable so the game can load its textures, shaders, and font.

Development builds are also available from the [latest successful GitHub Actions run](https://github.com/Dumr3n/FloppyRocket/actions/workflows/ci.yml). Open a run and download the **FloppyRocket-Windows-x64** artifact from its Artifacts section. GitHub may require you to sign in to download workflow artifacts.

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

Run `bin/Release-windows-x64/Sandbox/FloppyRocket.exe`. Game assets are copied beside the executable automatically.

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
`-- .github/        # CI and downloadable release builds
```

`GameLayer` coordinates application state and presentation. `Level` owns procedural hazards and collision checks, `Player` handles motion and input, and `ParticleSystem` renders rocket effects. Renderer-independent calculations live in `GameMath`, keeping important gameplay rules straightforward to test.

## Screenshots

<p align="center">
  <img width="49%" alt="Floppy Rocket obstacle course" src="https://github.com/user-attachments/assets/60894562-6e78-4fd6-87e3-d504b75eb394" />
  <img width="49%" alt="Floppy Rocket gameplay" src="https://github.com/user-attachments/assets/aa4919ee-fd53-4d67-91dc-d59fefdf01fc" />
</p>

## Acknowledgements

The game is built on the included [Hazel](https://github.com/TheCherno/Hazel) engine architecture and uses OpenGL, GLFW, Dear ImGui, GLM, and GoogleTest.
