#ifndef TRAIN_SYSTEM_H
#define TRAIN_SYSTEM_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <memory>
#include <utility> // For std::pair
#include <nlohmann/json.hpp> 
using json = nlohmann::json;

// Hash function for std::pair
struct pair_hash {
  template <typename T1, typename T2>
  size_t operator()(const std::pair<T1, T2>& p) const {
    auto h1 = std::hash<T1>()(p.first);
    auto h2 = std::hash<T2>()(p.second);
    return h1 ^ (h2 << 1);
  }
};

struct Station {
  std::string name;
  explicit Station(const std::string& name);
};

class Train {
public:
  double speed;
  explicit Train(double speed);
  void move(double distance);
};

// Loading configuration from JSON
class ConfigLoader {
public:
  std::vector<std::unique_ptr<Station>> stations;
  std::vector<std::unique_ptr<Train>> trains;

  void load_config(const std::string& filepath);
};

bool check_collisions(const std::unordered_map<std::pair<Station*, Station*>, std::unordered_set<int>, pair_hash>& track_usage);

#endif // TRAIN_SYSTEM_H
