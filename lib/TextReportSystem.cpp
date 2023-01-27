#include "TextReportSystem.h"

inline void OpenFile(std::ifstream& file, const std::filesystem::path& path_to_file) {
  file.exceptions(std::ifstream::badbit);
  try {
    file.open(path_to_file);
  } catch (const std::ifstream::failure& e) {
    std::cout << "Exception opening/reading file" << e.what() << std::endl;
  }
}

inline void OpenFile(std::ofstream& file, const std::filesystem::path& path_to_file) {
  file.exceptions(std::ifstream::badbit);
  try {
    file.open(path_to_file);
  } catch (const std::ofstream::failure& e) {
    std::cout << "Exception opening/reading file" << e.what() << std::endl;
  }
}

TextReportSystem::~TextReportSystem() {
  file_with_pattern_.close();
  file_with_parameters_.close();
}

void TextReportSystem::GetReport(std::filesystem::path& path_to_pattern, std::filesystem::path& path_to_parameters) {
  OpenFile(file_with_pattern_, path_to_pattern);
  OpenFile(file_with_parameters_, path_to_parameters);

  SetValue();

  file_with_parameters_.close();
  file_with_report_.close();
}

inline bool IsImportantParameter(const std::string& line) {
  return line.find('*') != std::string::npos;
}

const std::string TextReportSystem::SetParametersInLine(std::string& line) {
  const std::regex rex(R"(\{[*\w]+\})");
  std::sregex_iterator beg{line.cbegin(), line.cend(), rex};
  std::sregex_iterator end{};

  std::string new_line = line;
  int delta = 0;

  for (auto parameter = beg; parameter != end; ++parameter) {
    std::string value;
    std::getline(file_with_parameters_, value);

    if (IsImportantParameter(parameter->str()) && value.empty()) {
       throw std::invalid_argument("All important parameters must have values\n");
    }

    new_line = new_line.substr(0, parameter->position() - delta) + value
      + new_line.substr(parameter->position() + parameter->length() - delta);

    delta += parameter->length() - value.size();

  }

  return new_line;
}

void TextReportSystem::AddInReport(std::string& line) {
  report_ += line + '\n';
}

inline void WriteInFile(std::ofstream& file_for_writing, const std::string& line) {
  file_for_writing << line;
}

void TextReportSystem::SetValue() {
  std::string line;
  while (std::getline(file_with_pattern_, line)) {
    try {
      std::string new_line = SetParametersInLine(line);
      AddInReport(new_line);
    } catch (const std::exception& e) {
      std::cout << e.what();
    }
  }

  OpenFile(file_with_report_, "./report.txt");
  WriteInFile(file_with_report_, report_);
  file_with_report_.close();
}
