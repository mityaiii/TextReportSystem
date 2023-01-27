#include "./lib/TextReportSystem.h"

int main(int argc, char** argv) {
  TextReportSystem text_report_system;
  std::filesystem::path path_to_pattern = "D://pattern.txt";
  std::filesystem::path path_to_parameters = "D://parameters.txt";

  text_report_system.GetReport(path_to_pattern, path_to_parameters);

  return 0;
}
