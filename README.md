### Chess Game (SFML)

Simple two-player chess game implemented in modern C++ using SFML.

- **Language**: C++17
- **Library**: SFML (graphics, window, system, audio)
- **Platforms**: macOS, Linux, Windows

### Features
- Legal chess moves with checks for check, checkmate, stalemate
- Pawn promotion, short/long castling
- Sound effects for moves, captures, check, checkmate, stalemate
- Responsive board sizing

### Build (Cross-Platform via CMake)

Prerequisites:
- Install SFML 2.5+
- Install CMake 3.15+

macOS (Homebrew):
```bash
brew install sfml cmake
./scripts/build_macos.sh
CHESS_GAME_RESOURCES="$(pwd)/resources" ./build/macos/chess
```

Linux (Debian/Ubuntu):
```bash
sudo apt-get update && sudo apt-get install -y libsfml-dev cmake g++
./scripts/build_linux.sh
CHESS_GAME_RESOURCES="$(pwd)/resources" ./build/linux/chess
```

Windows (MSVC):
1. Install CMake and SFML for Windows.
2. Optionally set `SFML_DIR_HINT` to SFML's CMake config path (e.g. `C:\SFML\lib\cmake\SFML`).
3. Run:
```bat
scripts\build_windows.bat
set CHESS_GAME_RESOURCES="%cd%\resources" && build\windows\Release\chess.exe
```

Notes:
- The game locates resources at runtime. You can override the resource path with env var `CHESS_GAME_RESOURCES`.
- A legacy `sources/Makefile` is still available for simple Linux builds (inside `sources/`), but CMake is recommended.

### Run
If you run the binary from the project root, it will auto-detect `resources/`.
Otherwise, set the env var:
```bash
CHESS_GAME_RESOURCES="/absolute/path/to/resources" ./chess
```

### Project Structure
- `sources/`: C++ source code
- `resources/images/pieces`: piece sprites
- `resources/sounds`: sound effects
- `scripts/`: cross-platform build scripts

### License
See `LICENSE`.
