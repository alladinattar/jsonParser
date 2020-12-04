// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "jsonParser.hpp"

TEST(jsonParser, empty_path){
  ASSERT_THROW(jsonParser(""), std::invalid_argument);
}

TEST(jsonParser, empty_array){
  ASSERT_THROW(jsonParser((R"({})")), std::invalid_argument);
}

TEST(jsonParser, simple_array){
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
  ASSERT_EQ(formatter.getStudentString(2),
            "| Pertov Nikita | IU8-31 | 3.33 | Network |");
}

TEST(jsonParser, invalid_path){
  ASSERT_THROW(jsonParser("/sd.json"), std::out_of_range);
}

TEST(jsonParser, correct_file){
  ASSERT_THROW(jsonParser("tes.json"), std::out_of_range);
}

TEST(jsonParser, size_test){
  ASSERT_THROW(jsonParser(R"({
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
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 5
  }
})"), std::out_of_range);
}


TEST(jsonParser, correct_out){
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
        "C++",
        "Linux",
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
  ASSERT_EQ(formatter.getStudentString(0),
            "| Ivanov Petr   | 1      | 4.25 | null    |");
  ASSERT_EQ(formatter.getStudentString(1),
            "| Sidorov Ivan  | 31     | 4    | C++     |");
  ASSERT_EQ(formatter.getStudentString(2),
            "| Pertov Nikita | IU8-31 | 3.33 | 3 items |");
}
