# 🎮 Tetris Game

A simple implementation of the classic Tetris game written in C++ using a custom build system powered by [Premake](https://premake.github.io/). This project was created for educational purposes and demonstrates game loop mechanics, collision detection, rendering, and input handling.

## 📦 Features

- Classic Tetris gameplay
- Basic scoring system
- Game over states

## 🛠️ Built With

- **Language**: C++
- **Build System**: [Premake5](https://premake.github.io/)
- **Graphics**: [SFML](https://www.sfml-dev.org/)
- **Platform**: Windows

## 🚀 Getting Started

### 1. Clone the Repository

Open CMD or Git Bash And Type: git clone https://github.com/RoastedKaju/Tetris.git

### 2. Generate Project files

- Run GenerateProject.bat
OR
- Open CMD and type call "Vendor\Premake\premake5.exe vs2022"

### 3. Build The project

- Press "Ctrl + B"
OR
- Right click on Tetris Project in your solution explorer and click build.

## 📁 Directory Structure

Tetris/
|- Source/             # Game source files
|- ThirdParty/SFML/    # SFML library
|- premake5.lua        # Premake build script
|- Vendor/Premake      # Premake executeable
|- Binaries/           # Output binaries
|- README.md           # You're here!


