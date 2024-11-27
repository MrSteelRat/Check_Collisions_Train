#include "train_system.h"

// Реализация конструктора Station
Station::Station(const std::string& name) : name(name) {}

// Реализация конструктора Train
Train::Train(double speed) : speed(speed) {}

// Реализация метода движения поезда
void Train::move(double distance) {
  std::cout << "Train moving " << distance << " km at speed " << speed << " km/h.\n";
}

// Реализация проверки на столкновения
bool check_collisions(const std::unordered_map<std::pair<Station*, Station*>, std::unordered_set<int>, pair_hash>& track_usage) {
  for (auto it = track_usage.begin(); it != track_usage.end(); ++it) {
    if (it->second.size() > 1) {
      return true; // Обнаружено столкновение
    }
  }
  return false;
}
