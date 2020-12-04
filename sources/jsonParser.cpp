//
// Copyright 2020 Rinat Mukaev <rinamuka4@gmail.com>
//

#include "jsonParser.hpp"

#include <fstream>

#include "any"
#include "iostream"
#include "nlohmann/json.hpp"
#include "student.hpp"
#include "vector"
using nlohmann::json;

// construtor
jsonParser::jsonParser(std::string jsonPath) {
  if (jsonPath[0] != '{') {
    if (jsonPath.empty())
      throw std::invalid_argument("the path isn't available");
    std::ifstream file(jsonPath);
    if (!file) {
      throw std::out_of_range{"unable to open json: " + jsonPath};
    }
    file >> data;
  } else {
    data = json::parse(jsonPath);
  }
  if (data.empty()) {
    throw std::invalid_argument("Object array is empty");
  }

  if (!data.at("items").is_array()) {
    throw std::invalid_argument("JSON file is not array");
  }
  if (data.at("items").size() != data.at("_meta").at("count")) {
    throw std::out_of_range("_meta.count != len of items");
  }
}

// parse json to vector of students
void jsonParser::parseData() {
  for (auto const& item : data.at("items")) {
    auto studentObj = item.get<student>();
    students.push_back(studentObj);
  }
}

std::vector<student> jsonParser::getStudentsVector() { return students; }

auto get_name(const json& j) -> std::string { return j.get<std::string>(); }

auto get_debt(const json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::vector<std::string>>();
}

auto get_avg(const json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else if (j.is_number_float())
    return j.get<double>();
  else
    return j.get<std::size_t>();
}

auto get_group(const json& j) -> std::any {
  if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::size_t>();
}

void from_json(const json& j, student& s) {
  s.name = get_name(j.at("name"));
  s.group = get_group(j.at("group"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_debt(j.at("debt"));
}
