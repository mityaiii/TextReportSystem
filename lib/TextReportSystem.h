#pragma once

#include "Parser.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>

class TextReportSystem {
private:
//  class MyException : public std::exception {
//  private:
//  public:
//    MyException(const char* msg) : std::exception(msg) {
//
//    }
//  };

  std::ifstream file_with_pattern_;
  std::ifstream file_with_parameters_;

  std::ofstream file_with_report_;

  std::string report_;

  void AddInReport(std::string& line);

  void SetValue();
public:
  ~TextReportSystem();

  void GetReport(std::filesystem::path& path_to_pattern, std::filesystem::path& path_to_parameters);
  const std::string SetParametersInLine(std::string& line);
};
