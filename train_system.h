#ifndef TRAIN_SYSTEM_H
#define TRAIN_SYSTEM_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <memory>
#include <utility> // For std::pair
#include <nlohmann/json.hpp> // Подключение nlohmann/json
//#include "third_party/json/include/nlohmann/json.hpp" 
using json = nlohmann::json;

// Хеш-функция для std::pair
struct pair_hash {
  template <typename T1, typename T2>
  size_t operator()(const std::pair<T1, T2>& p) const {
    auto h1 = std::hash<T1>()(p.first);
    auto h2 = std::hash<T2>()(p.second);
    return h1 ^ (h2 << 1);
  }
};

// Класс для станции
struct Station {
  std::string name;
  explicit Station(const std::string& name);
};

// Класс для поезда
class Train {
public:
  double speed;
  explicit Train(double speed);
  void move(double distance);
};

// Загрузка конфигурации из JSON
class ConfigLoader {
public:
  std::vector<std::unique_ptr<Station>> stations;
  std::vector<std::unique_ptr<Train>> trains;

  void load_config(const std::string& filepath);
};

// Проверка на столкновения
bool check_collisions(const std::unordered_map<std::pair<Station*, Station*>, std::unordered_set<int>, pair_hash>& track_usage);

#endif // TRAIN_SYSTEM_H
