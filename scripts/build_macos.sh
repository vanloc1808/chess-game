#!/usr/bin/env bash
set -euo pipefail

# Build script for macOS
# Prereq: brew install sfml cmake

ROOT_DIR="$(cd "$(dirname "$0")"/.. && pwd)"
BUILD_DIR="$ROOT_DIR/build/macos"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake -DCMAKE_BUILD_TYPE=Release "$ROOT_DIR"
cmake --build . --config Release -j

echo
echo "Build complete. Binary located at: $BUILD_DIR/chess"
echo "Run with: CHESS_GAME_RESOURCES=\"$ROOT_DIR/resources\" $BUILD_DIR/chess"


