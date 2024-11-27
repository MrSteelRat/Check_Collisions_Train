#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <utility> // For std::pair
#include <memory>  // For smart pointers


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
  double speed;
  explicit Train(double speed) : speed(speed) {}

  void move(double distance, const std::unordered_map<std::pair<Station*, Station*>, int, pair_hash>& track_usage) {
    // Simulate the train moving and updating track usage
    std::cout << "Train moving " << distance << " km at speed " << speed << " km/h.\n";
  }
};

bool check_collisions(const std::unordered_map<std::pair<Station*, Station*>, std::unordered_set<int>, pair_hash>& track_usage) {
  for (auto it = track_usage.begin(); it != track_usage.end(); ++it) {
    if (it->second.size() > 1) {
      return true; // Collision detected
    }
  }
  return false;
}

int main() {
  // Create stations
  auto station1 = std::make_unique<Station>("Station A");
  auto station2 = std::make_unique<Station>("Station B");

  // Create trains
  Train train1(100);
  Train train2(80);

  // Track usage mapping
  std::unordered_map<std::pair<Station*, Station*>, std::unordered_set<int>, pair_hash> track_usage;

  // Example: Updating track usage
  track_usage[{station1.get(), station2.get()}].insert(1);
  track_usage[{station1.get(), station2.get()}].insert(2);

  // Check for collisions
  if (check_collisions(track_usage)) {
    std::cout << "Collision detected on the tracks!\n";
  }
  else {
    std::cout << "No collisions detected.\n";
  }

  // Train movement
  train1.move(10.5, {});

  return 0;
}
