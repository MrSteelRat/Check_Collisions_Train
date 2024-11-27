#include "train_system.h"

int main() {
  // create station
  auto station1 = std::make_unique<Station>("Station A");
  auto station2 = std::make_unique<Station>("Station B");

  // create train
  Train train1(100);
  Train train2(80);

  // map use path 
  std::unordered_map<std::pair<Station*, Station*>, std::unordered_set<int>, pair_hash> track_usage;

  // Обновляем использование путей
  track_usage[{station1.get(), station2.get()}].insert(1);
  track_usage[{station1.get(), station2.get()}].insert(2);

  if (check_collisions(track_usage)) {
    std::cout << "Collision detected on the tracks!\n";
  }
  else {
    std::cout << "No collisions detected.\n";
  }

  // Движение поезда
  train1.move(10.5);

  return 0;
}
