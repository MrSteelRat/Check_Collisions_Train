#ifndef TRAIN_SYSTEM_H
#define TRAIN_SYSTEM_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <fstream>

// Custom hash function for pairs
struct pair_hash {
  template <typename T1, typename T2>
  size_t operator()(const std::pair<T1, T2>& p) const {
    auto h1 = std::hash<T1>()(p.first);
    auto h2 = std::hash<T2>()(p.second);
    return h1 ^ (h2 << 1);
  }
};

// Class representing a Station
struct Station {
  std::string name;
  explicit Station(const std::string& name) : name(name) {}
};

// Class representing a Train
class Train {
public:
  int id;
  double speed;
  std::vector<std::string> route; // List of station names representing the route

  Train(int id, double speed, const std::vector<std::string>& route)
    : id(id), speed(speed), route(route) {
  }

  void move(const std::unordered_map<std::pair<std::string, std::string>, int, pair_hash>& track_lengths);
};

// Main Train System
class TrainSystem {
private:
  std::unordered_map<std::string, std::unique_ptr<Station>> stations; // Map station names to objects
  std::unordered_map<std::pair<std::string, std::string>, int, pair_hash> track_lengths; // Tracks and their lengths
  std::unordered_map<std::pair<std::string, std::string>, std::unordered_set<int>, pair_hash> track_usage; // Tracks and train IDs using them

public:
  void load_config(const std::string& config_file);
  void simulate();
  bool check_collisions() const;
};

#endif // TRAIN_SYSTEM_H
