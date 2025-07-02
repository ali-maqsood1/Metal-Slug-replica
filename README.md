# 🎮 Metal Slug Replica (C++ & Raylib)

A side-scrolling, run-and-gun **Metal Slug-style** game built entirely in **C++** using **Raylib**. Inspired by the arcade classic, this project features modular design with game objects, enemies, bullets, and player controls all written using modern C++ principles.

---

## 💪 Features

* Side-scrolling gameplay with dynamic enemies
* Player movement, shooting, and jumping
* Collision detection (player/enemy, bullets/enemies, etc.)
* Separate game states (Menu, Play, Pause, Game Over)
* Clean modular C++ codebase with `.cpp/.h` pairs
* Compiled with a custom `Makefile`

---

## 🛠️ Requirements

* **C++17 or later**
* [Raylib](https://www.raylib.com/) 4.5+

---

## 📄 How to Download & Run

### 1. Install Raylib

#### macOS (via Homebrew):

```bash
brew install raylib
```

#### Ubuntu:

```bash
sudo apt install libraylib-dev
```

#### Windows:

* Download Raylib from [https://www.raylib.com/](https://www.raylib.com/)
* Follow setup instructions for MinGW or MSVC

### 2. Clone the Repository

You can clone or download as ZIP using the green **Code** button.

### 3. Build the Game

Run this in the project folder:

```bash
make
```

### 4. Play

```bash
./main
```

Or double-click the compiled executable if you're on Windows/macOS.

---

## 📁 Folder Structure

```
Final Metal Slug/
├── assets/                # Sprites, sounds, etc.
├── Bullet.cpp/h
├── Enemy.cpp/h
├── Game.cpp/h
├── GameObject.cpp/h
├── GameState.cpp/h
├── GroundEnemy.cpp/h
├── Level.cpp/h
├── Player.cpp/h
├── SkyEnemy.cpp/h
├── SkyEnemyBullet.cpp/h
├── MAIN.cpp              # Entry point
├── main                  # Compiled binary
├── Makefile
└── README.md
```

---

## 🏖️ Makefile Overview

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I.
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

clean:
	rm -f *.o $(EXEC)
```

* Automatically finds and compiles all `.cpp` files.
* Links them with Raylib and system libraries.
* Use `make clean` to remove build artifacts.

---

## ✨ Credits

Developed by Ali Maqsood(https://github.com/ali-maqsood1)

Thanks to the Raylib community and Metal Slug for endless inspiration.

---

## 📄 License

This project is released under the **MIT License**.
