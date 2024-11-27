# Train Collision Detection System

This project simulates a train collision detection system. It uses the [nlohmann/json](https://github.com/nlohmann/json) library to load configurations from a JSON file. The project demonstrates the use of data structures like `std::unordered_map` and `std::unordered_set` to track train movements and prevent collisions.

## Features
- Simulates train movement between stations.
- Detects potential collisions on shared tracks.
- Loads configuration (e.g., train speeds, station names) from an external JSON file.

---

## Requirements

### Windows
1. Install a C++ compiler with C++20 support (e.g., Visual Studio 2022).
2. Clone the nlohmann/json library:
   ```bash
   git clone https://github.com/nlohmann/json.git in third_party_


### Linux
   ```bash
1. sudo apt update
2. sudo apt install cmake
3. sudo apt install nlohmann-json3-dev g++
