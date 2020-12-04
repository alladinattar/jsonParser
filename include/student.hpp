//
// Copyright 2020 Rinat Mukaev <rinamuka4@gmail.com>
//

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include "any"
#include "iostream"
#include "nlohmann/json.hpp"
#include "string"
#include "vector"

using nlohmann::json;
using std::any;
using std::string;
class student {
 public:
  std::string name;
  std::any group;
  std::any debt;
  std::any avg;
  std::string getName() const;
  std::string getGroup() const;
  std::string getDebt() const;
  std::string getAvg() const;
};

class studentsFormatter {
 private:
  size_t nameWidth;
  size_t groupWidth;
  size_t avgWidth;
  size_t debtWidth;
  std::vector<student> students;

 public:
  size_t getNameWidth();
  size_t getGroupWidth();
  size_t getAvgWidth();
  size_t getDebtWidth();
  explicit  studentsFormatter(std::vector<student> studentsArr);  //
  std::string getStudentString(int indexOfStudent);
  std::string getStudentsTable();
};

#endif  // INCLUDE_STUDENT_HPP_
