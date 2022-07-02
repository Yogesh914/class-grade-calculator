#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include<set>
#include<map>
#include<fstream>

int GetPointTotalForStudent (std::map<std::string,std::string> const &student_info, std::string const &category);
int GetTopNHomeworkTotalForStudent (std::map<std::string,std::string> const &student_info, int const &num);
int GetNumberOfMissingLabsForStudent (std::map<std::string,std::string> const &student_info);
int GetPointTotalForStudent (std::map<std::string,std::string> const &student_info);
std::map<std::string, std::map<std::string, std::string>> GetIDToInfoFromCSV (std::string const &filename);
std::map<std::string, double> GetIDToGrade(std::map<std::string, std::map<std::string, std::string>> const &id_to_info);
std::set<std::string> GetStudentsEligibleForHonorsCredit(std::map<std::string, std::map<std::string, std::string>> const &id_to_info, int const &n);