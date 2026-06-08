#!/bin/bash

# Build script untuk project C++ Balatro Game

echo "Building Balatro Game..."

# Collect all source files except test_main.cpp
files=()
while IFS= read -r file; do
    files+=("$file")
done < <(find src -name "*.cpp" ! -name "test_main.cpp" | sort)

# Convert Windows-style paths to Unix-style untuk g++
echo "Compiling sources..."
g++ -fdiagnostics-color=always -g "${files[@]}" -o "balatro_game.exe"

if [ $? -eq 0 ]; then
    echo "Build successful! Output: balatro_game.exe"
    ls -la balatro_game.exe
else
    echo "Build failed!"
    exit 1
fi
