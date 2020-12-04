// Copyright 2020 Rinat Mukaev <rinamuka4@gmail.com>

#ifndef INCLUDE_JSONPARSER_HPP_
#define INCLUDE_JSONPARSER_HPP_
#include "any"
#include "iostream"
#include "nlohmann/json.hpp"
#include "sstream"
#include "string"
#include "student.hpp"
#include "vector"
using nlohmann::json;
using std::any;
using std::string;

void from_json(const json& j, student& s);
auto get_name(const json& j) -> std::string;
auto get_debt(const json& j) -> std::any;
auto get_avg(const json& j) -> std::any;
auto get_group(const json& j) -> std::any;

class jsonParser {
 private:
  nlohmann::json data;
  std::vector<student> students;

 public:
  explicit jsonParser(string);  // Check all exeptions and >> data
  void parseData();
  std::vector<student> getStudentsVector();
};

/*auto get_name(const json& j) -> std::string { return j.get<std::string>(); }
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
  else if (j.is_number_integer())
    return j.get<int>();
  else
    return j.get<size_t>();
}

auto get_group(const json& j) -> std::any {
  if (j.is_string())
    return j.get<std::string>();
  else if (j.is_number_integer())
    return j.get<int>();
  else
    return j.get<size_t>();
}


class jsonParser{
 private:
  std::stringstream ss;
  jsonParser(std::string jsonPath);
};*/
#endif  // INCLUDE_JSONPARSER_HPP_
