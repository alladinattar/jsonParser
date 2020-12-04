// Copyright 2020 Your Name <your_email>
#include "iostream"
#include "jsonParser.hpp"
#include "student.hpp"

int main() {
  jsonParser parser = jsonParser(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
  parser.parseData();
  studentsFormatter formatter = studentsFormatter(parser.getStudentsVector());
  std::cout << formatter.getStudentString(2);
  std::cout << formatter.getStudentsTable();
}
