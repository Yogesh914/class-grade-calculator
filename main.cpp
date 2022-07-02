#include "main.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<set>
#include<map>
#include<fstream>
#include <iterator>
#include <numeric>
#include <exception>
#include <sstream>

//Function using try catch to convert string into int value
int ConvertToInt(std::string
  const & num) {
  try {
    return std::stoi(num);
  } catch (...) {
    return 0;
  }
}

//Get total points f or a student in a specific category
int GetPointTotalForStudent(std::map < std::string, std::string >
  const & student_info, std::string
  const & category) {
  std::vector < int > scores;
  int total = 0;
  //Using transform to capture all the numbers in a category and store it in a vector
  //To help with transform in maps: https://stackoverflow.com/questions/7879326/how-to-apply-transform-to-an-stl-map-in-c
  std::transform(student_info.begin(), student_info.end(), std::back_inserter(scores),
    [ & ](std::pair < std::string, std::string > element) {
      if (element.first.find(category) != std::string::npos) {

        return ConvertToInt(element.second);
      } else {
        return 0;
      }
    }
  );

  //total up the scores in the vector and return it
  total = std::accumulate(scores.begin(), scores.end(), 0);
  return total;

}

int GetTopNHomeworkTotalForStudent(std::map < std::string, std::string >
  const & student_info, int
  const & n) {
  std::vector < int > scores;
  int total = 0;
  //Using transform to capture all the hw scores and store it in a vector
  std::transform(student_info.begin(), student_info.end(), std::back_inserter(scores),
    [ & ](std::pair < std::string, std::string > element) {
      if (element.first.find("HW") != std::string::npos) {

        return ConvertToInt(element.second);
      } else {
        return 0;
      }
    }
  );
  //sort the vector and then total up the top n homeworks
  std::sort(scores.begin(), scores.end(), std::greater < int > ());
  total = std::accumulate(scores.begin(), scores.begin() + n, 0);
  return total;
}

int GetNumberOfMissingLabsForStudent(std::map < std::string, std::string >
  const & student_info) {
  std::vector < int > scores;
  int total = 0;
  //Using transform to collect all the Lab absences 
  std::transform(student_info.begin(), student_info.end(), std::back_inserter(scores),
    [ & ](std::pair < std::string, std::string > element) {
      if (element.first.find("Lab") != std::string::npos) {

        int value = ConvertToInt(element.second);
        if (value == 1) {
          return 0;
        } else {
          return 1;
        }
      } else {
        return 0;
      }
    }
  );

  total = std::accumulate(scores.begin(), scores.end(), 0);
  return total;
}

//Get total points f or a student
int GetPointTotalForStudent(std::map < std::string, std::string >
  const & student_info) {
  std::vector < int > scores;
  int total = 0;

  //transforms only if category is not Labs, Honors and HW -> because only top homeworks are added
  std::transform(student_info.begin(), student_info.end(), std::back_inserter(scores),
    [ & ](std::pair < std::string, std::string > element) {
      if (element.first.find("Lab") != std::string::npos || element.first.find("Honors") != std::string::npos || element.first.find("HW") != std::string::npos) {

        return 0;
      }
      return ConvertToInt(element.second);

    }
  );
  total = std::accumulate(scores.begin(), scores.end(), 0);
  total += GetTopNHomeworkTotalForStudent(student_info, 15);
  return total;
}

//Convert a string line into vector of strings
std::vector < std::string > LineToVector(std::vector < std::string > vector, std::string line) {

  //using generate to iterate and store each word from line split by commas
  std::generate(vector.begin(), vector.end(), [ & ]() mutable {
    if (line.find(',') == -1) {
      line = "";
      return line;
    } else {
      int index = line.find_first_of(',');
      std::string value = line.substr(0, index);
      line.erase(0, index + 1);
      return value;
    }
  });
  return vector;
}

std::map < std::string, std::map < std::string, std::string >> GetIDToInfoFromCSV(std::string
  const & filename) {

  std::map < std::string, std::map < std::string, std::string >> id_to_student_info;
  std::map < std::string, std::string > item;

  std::ifstream file;
  std::string line;
  file.open(filename);
  getline(file, line);
  line += ',';
  int size = std::count(line.begin(), line.end(), ',');
  std::vector < std::string > values(size);
  std::vector < std::string > header(size); //used as keys

  header = LineToVector(header, line);

  //loop over each line of the csv file to store values
  while (file.is_open() && !file.eof()) {
    item.clear();
    getline(file, line);
    line += ',';

    values = LineToVector(values, line);

    std::map < std::string, std::string > item;

    //loop to store all values into a pair and then into a map
    for (int i = 0; i < header.size(); i++) {
      item.insert(std::pair < std::string, std::string > (header.at(i), values.at(i)));
    }
    id_to_student_info.insert(std::pair < std::string, std::map < std::string, std::string >> (values.at(1), item));

  }

  return id_to_student_info;
}

//Convert the totals into GPAs
double getGrade(int
  const & n) {
  if (n >= 900 && n <= 1000) {
    return 4.0;
  }
  if (n >= 850 && n <= 899) {
    return 3.5;
  }
  if (n >= 800 && n <= 849) {
    return 3.0;
  }
  if (n >= 750 && n <= 799) {
    return 2.5;
  }
  if (n >= 700 && n <= 749) {
    return 2.0;
  }
  if (n >= 650 && n <= 699) {
    return 1.5;
  }
  if (n >= 600 && n <= 649) {
    return 1.0;
  }
  if (n >= 0 && n <= 599) {
    return 0.0;
  }
  return 0;
}

//Count the labs missed using transform
int LabCounter(auto it, std::vector < int > labs) {

  std::transform(it -> second.begin(), it -> second.end(), std::back_inserter(labs),
    [ & ](std::pair < std::string, std::string > element) {

      int marks = 0;
      marks = ConvertToInt(element.second);
      if (element.first.find("Lab") != std::string::npos) {
        if (marks == 0) {
          return 1;
        }
      }
      return 0;
    }
  );
  int total = 0;
  total = std::accumulate(labs.begin(), labs.end(), 0);
  return total;

}

std::map < std::string, double > GetIDToGrade(std::map < std::string, std::map < std::string, std::string >>
  const & id_to_student_info) {
  std::map < std::string, double > remap;
  auto it = id_to_student_info.begin();
  //loop iterating through map
  while (it != id_to_student_info.end()) {
    std::vector < int > labs;

    int score = 0;
    std::string id = it -> first;
    score = GetPointTotalForStudent(id_to_student_info.at(id));

    int labcount = LabCounter(it, labs);
    double grades = getGrade(score);
    if (labcount > 2 && grades > 0) {
      grades = grades - ((labcount - 2) * 0.5);
      labcount = 0;
    }
    remap.insert({
      id,
      grades
    });
    it++;
  }
  return remap;
}

std::set < std::string > GetStudentsEligibleForHonorsCredit(std::map < std::string, std::map < std::string, std::string >>
  const & id_to_student_info, int
  const & n) {

  std::set < std::string > strset;
  auto it = id_to_student_info.begin();
  //loop iterating through map
  while (it != id_to_student_info.end()) {
    std::vector < int > labs;
    int score = 0;
    std::string id = it -> first;
    score = GetPointTotalForStudent(id_to_student_info.at(id));

    int labcount = LabCounter(it, labs);
    double grades = getGrade(score);
    if (labcount > 2 && grades > 0) {
      grades = grades - ((labcount - 2) * 0.5);
      labcount = 0;
    }
    if (grades >= 3.5) {
      int ph = ConvertToInt(id_to_student_info.at(id).at("Project Honors"));
      if (ph >= 9) {
        strset.insert(id);
      }
    }
    it++;
  }
  return strset;
}

int main() {
    return 0;
}