#include "train_system.h"
#include <fstream>

// Implementation of the Station constructor
Station::Station(const std::string& name) : name(name) {}

// Implementation of the Train constructor
Train::Train(double speed) : speed(speed) {}

// Implementation of the train movement method
void Train::move(double distance) {
  std::cout << "Train moving " << distance << " km at speed " << speed << " km/h.\n";
}

// Loading configuration from a JSON file
void ConfigLoader::load_config(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open config file: " + filepath);
  }

  json config_json;
  file >> config_json;

  for (const auto& station_json : config_json["stations"]) {
    stations.emplace_back(std::make_unique<Station>(station_json["name"]));
  }

  for (const auto& train_json : config_json["trains"]) {
    trains.emplace_back(std::make_unique<Train>(train_json["speed"]));
  }
}

// Implementing collision checking
bool check_collisions(const std::unordered_map<std::pair<Station*, Station*>, std::unordered_set<int>, pair_hash>& track_usage) {
  for (const auto& [key, trains] : track_usage) {
    if (trains.size() > 1) {
      return true; // Collision detected
    }
  }
  return false;
}
