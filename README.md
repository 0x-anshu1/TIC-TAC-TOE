# Tic-Tac-Toe (TCP Sockets, C++)

A small client–server Tic-Tac-Toe game written in C++ using TCP sockets.  
Minimal, educational project demonstrating basic socket I/O, simple message passing, and turn-based game logic.

## Features
- Simple two-player client/server game over TCP
- Move validation and draw/win detection
- Text-based terminal UI
- Small, easy-to-read codebase for learning networking concepts

## Requirements
- Linux or WSL (Ubuntu/Debian)
- g++ (C++17 or later)
- `make` (optional)

## Build
Compile server and client from the project root:
```bash
g++ server.cpp game_fun.cpp -o server -std=c++17
g++ client.cpp game_fun.cpp -o client -std=c++17
