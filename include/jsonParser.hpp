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
  explicit jsonParser(string);
  void parseData();
  std::vector<student> getStudentsVector();
};

#endif  // INCLUDE_JSONPARSER_HPP_
