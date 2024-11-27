#include "train_system.h"
#include <fstream>

// Реализация конструктора Station
Station::Station(const std::string& name) : name(name) {}

// Реализация конструктора Train
Train::Train(double speed) : speed(speed) {}

// Реализация метода движения поезда
void Train::move(double distance) {
  std::cout << "Train moving " << distance << " km at speed " << speed << " km/h.\n";
}

// Загрузка конфигурации из файла JSON
void ConfigLoader::load_config(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open config file: " + filepath);
  }

  json config_json;
  file >> config_json;

  // Загрузка станций
  for (const auto& station_json : config_json["stations"]) {
    stations.emplace_back(std::make_unique<Station>(station_json["name"]));
  }

  // Загрузка поездов
  for (const auto& train_json : config_json["trains"]) {
    trains.emplace_back(std::make_unique<Train>(train_json["speed"]));
  }
}

// Реализация проверки на столкновения
bool check_collisions(const std::unordered_map<std::pair<Station*, Station*>, std::unordered_set<int>, pair_hash>& track_usage) {
  for (const auto& [key, trains] : track_usage) {
    if (trains.size() > 1) {
      return true; // Обнаружено столкновение
    }
  }
  return false;
}
