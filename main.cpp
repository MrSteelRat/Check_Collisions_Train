#include "train_system.h"

int main() {
  try {
    ConfigLoader config_loader;
    config_loader.load_config("config.json");

    std::cout << "Stations:\n";
    for (const auto& station : config_loader.stations) {
      std::cout << "- " << station->name << "\n";
    }

    std::cout << "\nTrains:\n";
    for (const auto& train : config_loader.trains) {
      std::cout << "- Speed: " << train->speed << " km/h\n";
    }

    // Example of using paths
    std::unordered_map<std::pair<Station*, Station*>, std::unordered_set<int>, pair_hash> track_usage;
    if (config_loader.stations.size() >= 2) {
      track_usage[{config_loader.stations[0].get(), config_loader.stations[1].get()}].insert(1);
    }

    // Checking for collisions
    if (check_collisions(track_usage)) {
      std::cout << "\nCollision detected on the tracks!\n";
    }
    else {
      std::cout << "\nNo collisions detected.\n";
    }

    // Example of train movement
    if (!config_loader.trains.empty()) {
      config_loader.trains[0]->move(15.5);
    }

  }
  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
