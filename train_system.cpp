#include "train_system.h"

void Train::move(const std::unordered_map<std::pair<std::string, std::string>, int, pair_hash>& track_lengths) {
  for (size_t i = 1; i < route.size(); ++i) {
    std::string from = route[i - 1];
    std::string to = route[i];
    auto track = std::make_pair(from, to);

    if (track_lengths.find(track) == track_lengths.end()) {
      throw std::runtime_error("No track exists between " + from + " and " + to);
    }

    int distance = track_lengths.at(track);
    std::cout << "Train " << id << " moving from " << from << " to " << to
      << " (" << distance << " km at speed " << speed << " km/h)\n";
  }
}

void TrainSystem::load_config(const std::string& config_file) {
  // Read JSON configuration
  std::ifstream file(config_file);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open config file: " + config_file);
  }

  nlohmann::json config;
  file >> config;

  // Load stations
  for (const auto& station : config["stations"]) {
    stations[station["name"]] = std::make_unique<Station>(station["name"]);
  }

  // Load tracks
  for (const auto& track : config["tracks"]) {
    std::string from = track["from"];
    std::string to = track["to"];
    int length = track["length"];

    track_lengths[{from, to}] = length;
    track_lengths[{to, from}] = length; // Assuming bidirectional tracks
  }

  // Load trains
  for (const auto& train : config["trains"]) {
    int id = train["id"];
    double speed = train["speed"];
    std::vector<std::string> route = train["route"];

    std::cout << "Train " << id << " loaded with speed " << speed
      << " km/h and route: ";
    for (const auto& station : route) {
      std::cout << station << " ";
    }
    std::cout << "\n";
  }
}

bool TrainSystem::check_collisions() const {
  for (const auto& track : track_usage) {
    if (track.second.size() > 1) {
      return true; // Collision detected
    }
  }
  return false;
}

void TrainSystem::simulate() {
  std::cout << "Simulating train movements...\n";
  // Add simulation logic here if needed
}
