//
// Copyright 2020 Rinat Mukaev <rinamuka4@gmail.com>
//
#include "student.hpp"
#include "iomanip"
#include "iostream"
#include "nlohmann/json.hpp"

using nlohmann::json;

std::string student::getName() const { return name; }

std::string student::getGroup() const {
  if (group.type() == typeid(std::string)) {
    return std::any_cast<string>(group);
  } else if (group.type() == typeid(int)) {
    return std::to_string(std::any_cast<int>(group));
  } else {
    return std::to_string(std::any_cast<size_t>(group));
  }
}

std::string student::getAvg() const {
  if (avg.type() == typeid(std::string)) {
    return std::any_cast<string>(avg);
  } else if (avg.type() == typeid(size_t)) {
    return std::to_string(std::any_cast<size_t>(avg));
  } else if (avg.type() == typeid(nullptr)) {
    return "null";
  } else {
    return std::to_string(std::any_cast<double>(avg)).substr(0, 4);
  }
}

std::string student::getDebt() const {
  if (debt.type() == typeid(std::string)) {
    return std::any_cast<string>(debt);
  } else if (debt.type() == typeid(nullptr)) {
    return "null";
  } else {
    if (std::any_cast<std::vector<string>>(debt).size() == 1){
      return std::any_cast<std::vector<string>>(debt)[0];
    }
    return std::to_string(std::any_cast<std::vector<string>>(debt).size()) +
           " items";
  }
}

studentsFormatter::studentsFormatter(std::vector<student> studentsArr)
    : nameWidth(4),
      groupWidth(5),
      avgWidth(3),
      debtWidth(4),
      students(studentsArr) {
  for (auto const& student : studentsArr) {
    if (student.getName().length() >= nameWidth) {
      nameWidth = student.getName().length();
    }
    if (student.getDebt().length() >= debtWidth) {
      debtWidth = student.getDebt().length();
    }
    if (student.getAvg().length() >= avgWidth) {
      avgWidth = student.getAvg().length();
    }
    if (student.getGroup().length() >= groupWidth) {
      groupWidth = student.getGroup().length();
    }
  }
}

std::string studentsFormatter::getStudentString(int indexOfStudent) {
  std::stringstream ss;
  ss << std::setw(2) << "| " << std::setw(nameWidth) << std::left
     << students[indexOfStudent].getName() << std::setw(3) << " | "
     << std::setw(groupWidth) << std::left
     << students[indexOfStudent].getGroup() << std::setw(3) << " | "
     << std::setw(avgWidth) << std::left << students[indexOfStudent].getAvg()
     << std::setw(3) << " | " << std::setw(debtWidth) << std::left
     << students[indexOfStudent].getDebt() << std::setw(2) << " |";
  return ss.str();
}

std::string studentsFormatter::getStudentsTable() {
  std::stringstream ss;
  ss << std::setw(2) << "| " << std::setw(nameWidth) << std::left << "name"
     << std::setw(3) << " | " << std::setw(groupWidth) << std::left << "group"
     << std::setw(3) << " | " << std::setw(avgWidth) << std::left << "avg"
     << std::setw(3) << " | " << std::setw(debtWidth) << "debt" << std::setw(2)
     << " |"
     << "\n";
  ss << std::setw(1) << "|" << std::setw(nameWidth + 2) << std::setfill('-')
     << "" << std::setw(1) << "|" << std::setw(groupWidth + 2)
     << std::setfill('-') << ""
     << "|" << std::setw(avgWidth + 2) << std::setfill('-') << ""
     << "|" << std::setw(debtWidth + 2) << std::setfill('-') << ""
     << std::setw(1) << "|"
     << "\n";
  for (size_t i = 0; i < students.size(); ++i) {
    if (i != students.size() - 1) {
      ss << getStudentString(i) << "\n";
    } else {
      ss << getStudentString(i)<<"\n";
    }
  }
  ss << std::setw(1) << "|" << std::setw(nameWidth + 2) << std::setfill('-')
     << "" << std::setw(1) << "|" << std::setw(groupWidth + 2)
     << std::setfill('-') << ""
     << "|" << std::setw(avgWidth + 2) << std::setfill('-') << ""
     << "|" << std::setw(debtWidth + 2) << std::setfill('-') << ""
     << std::setw(1) << "|";
  return ss.str();
}

std::size_t studentsFormatter::getNameWidth() { return nameWidth; }
std::size_t studentsFormatter::getGroupWidth() { return groupWidth; }
std::size_t studentsFormatter::getAvgWidth() { return avgWidth; }
std::size_t studentsFormatter::getDebtWidth() { return debtWidth; }
