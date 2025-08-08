@echo off
setlocal enabledelayedexpansion

REM Build script for Windows (MSVC)
REM Prereq: Install SFML and CMake. Optionally set SFML_DIR_HINT to SFML's cmake config path, e.g.
REM set SFML_DIR_HINT=C:\SFML\lib\cmake\SFML

set ROOT_DIR=%~dp0..\
for %%I in ("%ROOT_DIR%") do set ROOT_DIR=%%~fI
set BUILD_DIR=%ROOT_DIR%\build\windows

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
pushd "%BUILD_DIR%"

cmake -DCMAKE_BUILD_TYPE=Release -DSFML_DIR_HINT="%SFML_DIR_HINT%" "%ROOT_DIR%"
cmake --build . --config Release -j

echo.
if exist "%BUILD_DIR%\Release\chess.exe" (
  echo Build complete. Binary located at: %BUILD_DIR%\Release\chess.exe
  echo Run with: set CHESS_GAME_RESOURCES="%ROOT_DIR%\resources" ^&^& "%BUILD_DIR%\Release\chess.exe"
) else (
  echo Build complete. Binary located at: %BUILD_DIR%\chess.exe
  echo Run with: set CHESS_GAME_RESOURCES="%ROOT_DIR%\resources" ^&^& "%BUILD_DIR%\chess.exe"
)

popd
endlocal


