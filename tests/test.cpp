// Copyright 2020 Rinat <rinamuka4@gmail.com>

#include <gtest/gtest.h>
#include "jsonParser.hpp"

TEST(jsonParser, emptyPath){
  ASSERT_THROW(jsonParser(""), std::invalid_argument);
}

TEST(jsonParser, emptyArray){
  ASSERT_THROW(jsonParser((R"({})")), std::invalid_argument);
}

TEST(jsonParser, simpleArray){
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

TEST(jsonParser, invalidPath){
  ASSERT_THROW(jsonParser("/sd.json"), std::out_of_range);
}

TEST(jsonParser, correctFile){
  ASSERT_THROW(jsonParser("tes.json"), std::out_of_range);
}

TEST(jsonParser, sizeTest){
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


TEST(jsonParser, correctOut){
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


TEST(jsonParser, nullAvg){
  jsonParser parser = jsonParser(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": null,
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
            "| Ivanov Petr   | 1      | null | null    |");
  ASSERT_EQ(formatter.getStudentString(1),
            "| Sidorov Ivan  | 31     | 4    | C++     |");
  ASSERT_EQ(formatter.getStudentString(2),
            "| Pertov Nikita | IU8-31 | 3.33 | 3 items |");
}

TEST(jsonParser, printTable){
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
  ASSERT_EQ(formatter.getStudentsTable(),
            "| name          | group  | avg  | debt    |\n"
            "|---------------|--------|------|---------|\n"
            "| Ivanov Petr   | 1      | 4.25 | null    |\n"
            "| Sidorov Ivan  | 31     | 4    | C++     |\n"
            "| Pertov Nikita | IU8-31 | 3.33 | 3 items |\n"
            "|---------------|--------|------|---------|");
}


TEST(jsonParser, widthDebt){
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
ASSERT_EQ(formatter.getDebtWidth(), 7);
}


TEST(jsonParser, widthAvg){
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
  ASSERT_EQ(formatter.getAvgWidth(), 4);
}

TEST(jsonParser, nameAvg){
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
  ASSERT_EQ(formatter.getNameWidth(), 13);
}



TEST(jsonParser, groupWidth){
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
  ASSERT_EQ(formatter.getNameWidth(), 6);
}
