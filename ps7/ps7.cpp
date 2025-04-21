// Copyright Manasa Praveen 2025

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <iomanip>
#include <boost/date_time/posix_time/posix_time.hpp>

boost::posix_time::ptime parse_timestamp(const std::string& ts) {
  std::stringstream ss(ts);
  ss.imbue(std::locale(std::locale::classic(),
                       new boost::posix_time::time_input_facet("%b %d %H:%M:%S")));
  boost::posix_time::ptime pt;
  ss >> pt;
  return pt;
}

struct BootRecord {
  int start_line;
  std::string start_ts_str;
  boost::posix_time::ptime start_time;

  int end_line = -1;
  std::string end_ts_str;
  boost::posix_time::ptime end_time;

  bool complete = false;
  std::vector<std::pair<std::string, int>> services;
};

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./ps7 <input_log_file>" << std::endl;
    return 1;
  }

  std::string input_filename = argv[1];
  std::ifstream infile(input_filename);
  if (!infile.is_open()) {
    std::cerr << "Error: Cannot open file " << input_filename << std::endl;
    return 1;
  }

  std::string output_filename = input_filename + ".rpt";
  std::ofstream outfile(output_filename);

  std::regex start_re(
      R"((\w{3} \d{1,2} \d{2}:\d{2}:\d{2}).*\(log\.c\.166\) server started)");
  std::regex end_re(
      R"((\w{3} \d{1,2} \d{2}:\d{2}:\d{2}).*oejs\.AbstractConnector:Started SelectChannelConnector)");
  std::regex service_re(R"((\w+)\s*\([^)]*?(\d+)\s*ms\))");
  std::regex startupservlet_re(R"(StartupServlet Time\s*==>\s*(\d+)\s*ms)");

  std::string line;
  int line_number = 0;
  std::vector<BootRecord> boots;
  BootRecord current_boot;
  bool waiting_for_end = false;

  while (std::getline(infile, line)) {
    ++line_number;
    std::smatch match;

    if (std::regex_search(line, match, start_re)) {
      if (waiting_for_end) {
        boots.push_back(current_boot);
      }
      current_boot = BootRecord{
          line_number, match[1], parse_timestamp(match[1])};
      waiting_for_end = true;
    } else if (waiting_for_end && std::regex_search(line, match, end_re)) {
      current_boot.end_line = line_number;
      current_boot.end_ts_str = match[1];
      current_boot.end_time = parse_timestamp(match[1]);
      current_boot.complete = true;
      boots.push_back(current_boot);
      waiting_for_end = false;
    } else if (waiting_for_end && std::regex_search(line, match, service_re)) {
      std::string name = match[1];
      int duration = std::stoi(match[2]);
      current_boot.services.emplace_back(name, duration);
    } else if (waiting_for_end &&
               std::regex_search(line, match, startupservlet_re)) {
      current_boot.services.emplace_back("StartupServlet", std::stoi(match[1]));
    }
  }

  if (waiting_for_end) {
    boots.push_back(current_boot);
  }

  int total = static_cast<int>(boots.size());
  int successes = 0;
  long total_seconds = 0;
  long max_seconds = 0;

  for (const auto& b : boots) {
    if (b.complete) {
      boost::posix_time::time_duration diff = b.end_time - b.start_time;
      long seconds = diff.total_seconds();
      total_seconds += seconds;
      if (seconds > max_seconds) max_seconds = seconds;
      ++successes;
    }
  }

  outfile << "=== Boot Summary ===" << std::endl;
  outfile << "Total Boots: " << total << std::endl;
  outfile << "Successful Boots: " << successes << std::endl;
  outfile << "Failed Boots: " << total - successes << std::endl;
  if (successes > 0) {
    outfile << "Average Boot Time: " << std::fixed << std::setprecision(1)
            << static_cast<double>(total_seconds) / successes << " seconds"
            << std::endl;
    outfile << "Longest Boot Time: " << max_seconds << " seconds" << std::endl;
  }
  outfile << std::endl;

  for (const auto& b : boots) {
    outfile << "Line " << b.start_line << ": " << b.start_ts_str
            << " Boot Start" << std::endl;

    for (const auto& s : b.services) {
      outfile << "    " << s.first << " - " << s.second << " ms" << std::endl;
    }

    if (b.complete) {
      boost::posix_time::time_duration diff = b.end_time - b.start_time;
      outfile << "Line " << b.end_line << ": " << b.end_ts_str
              << " Boot Complete - " << diff.total_seconds() << " seconds"
              << std::endl;
    } else {
      outfile << "Line " << b.start_line
              << ": Boot Failure - No boot complete before next start or EOF"
              << std::endl;
    }

    outfile << std::endl;
  }

  std::cout << "Report written to " << output_filename << std::endl;
  return 0;
}
