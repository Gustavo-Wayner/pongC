***ATENTION*: I only have access to Windows and therefore am unable to confirm if my Makefile works on linux/mac. Feedback and fixes/tips from linux/mac users would be very much apreciated**
# 🎮 PongC

A small Pong clone written in C/C++ using [raylib](https://www.raylib.com/).  
It started simple... and then became way too complex for a Pong clone

> Purpose: practicing C, game architecture, and cross-platform builds.

## 📦 Dependencies

Required tools:

- **C++17** or newer
- **GNU make**
- **raylib** (included with the project)
- **gcc / clang / mingw-w64**

You **do NOT** need to install raylib manually.  
It is built from the repository source.

---

## 🛠️ Installing Build Tools

### 🐧 Linux (Debian/Ubuntu)

sudo apt update

sudo apt install build-essential git libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libxcursor-dev mesa-utils


### 🐧 Arch Linux
sudo pacman -S base-devel libx11 libxrandr libxi libxcursor mesa

### 🍎 MacOS (homebrew)
brew install make gcc raylib

### 🪟 Windows (MSYS2 + MinGW)
1 - Install MSYS2 → https://www.msys2.org/

2 - Open MSYS2 UCRT64 or MSYS2 MINGW64 and run:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make git

## 🚀 Building and Running

### In the terminal

▶️ Linux / macOS:

make;

make run;

make clean

🪟 Windows (MinGW):

mingw32-make;

mingw32-make run;

mingw32-make clean

### Through tasks

alternatively you can run the repective tasks in tasks.json, if in vs code

▶️ Linux / macOS:

build (make);

run (make);

clean (make)

🪟 Windows (MinGW):

windows build (make);

windows run (make);

windows clean (make)

#### No make
My college computers have no make nor can i install stuff in them. for that, and for those who are in a similar situation, i made tasks to compile without using make, just the terminal
**This still requires that computer to have a c++ compiler**

🪟 windows compile (no-make);

🐧 linux compile (no-make);

🍎 osx compile (no-make)

## Game Instructions
upping the number at line 54 in Rooms.cpp will make the game harder by making the opponent move faster

upping the ballMaxSpeed variable at Rooms.cpp line 53 sets the ball's max of course speed

the increment variable above them dictates by how much the ball's speed will be incremented each time it hits the paddles


## 📁 Project Structure
pongC/

 ├── .vscode/

 │   ├── tasks.json

 │   └── settings.json

 ├── src/

 │   ├── main.cpp

 │   ├── Rooms.cpp / .h

 │   ├── Objects.cpp / .h

 |   ├── Static.cpp / .h

 │   └── Structs.cpp / .h

 ├── raylib/              ← bundled raylib source

 ├── Makefile

 └── README.md