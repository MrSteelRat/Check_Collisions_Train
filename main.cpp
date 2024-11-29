#include "train_system.h"

int main() {
  TrainSystem train_system;

  try {
    // Load configuration from JSON
    train_system.load_config("config.json");

    // Simulate train movements
    train_system.simulate();

    // Check for collisions
    if (train_system.check_collisions()) {
      std::cout << "Collision detected on the tracks!\n";
    }
    else {
      std::cout << "No collisions detected.\n";
    }
  }
  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
  }

  return 0;
}
