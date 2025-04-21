// Copyright Manasa Praveen 2025

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <iomanip>
#include <cstdint>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

boost::posix_time::ptime parse_timestamp(const std::string& ts, int year) {
  std::stringstream ss;
  ss << year << " " << ts;
  ss.imbue(std::locale(std::locale::classic(),
                       new boost::posix_time::time_input_facet("%Y %b %d %H:%M:%S")));
  boost::posix_time::ptime pt;
  ss >> pt;
  return pt;
}

std::string format_datetime(const boost::posix_time::ptime& pt) {
  std::string date = boost::gregorian::to_iso_extended_string(pt.date());
  std::string time = boost::posix_time::to_simple_string(pt.time_of_day());
  return date + " " + time;
}

struct BootRecord {
  int start_line;
  std::string start_ts_str;
  boost::posix_time::ptime start_time;

  int end_line = -1;
  std::string end_ts_str;
  boost::posix_time::ptime end_time;

  bool complete = false;
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

  std::string line;
  int line_number = 0;
  std::vector<BootRecord> boots;
  BootRecord current_boot;
  bool waiting_for_end = false;
  const int inferred_year = 2014;

  while (std::getline(infile, line)) {
    ++line_number;
    std::smatch match;

    if (std::regex_search(line, match, start_re)) {
      if (waiting_for_end) {
        boots.push_back(current_boot);
      }
      current_boot = BootRecord{
          line_number, match[1], parse_timestamp(match[1], inferred_year)};
      waiting_for_end = true;
    } else if (waiting_for_end && std::regex_search(line, match, end_re)) {
      current_boot.end_line = line_number;
      current_boot.end_ts_str = match[1];
      current_boot.end_time = parse_timestamp(match[1], inferred_year);
      current_boot.complete = true;
      boots.push_back(current_boot);
      waiting_for_end = false;
    }
  }

  if (waiting_for_end) {
    boots.push_back(current_boot);
  }

  outfile << "InTouch log file: " << input_filename << std::endl;

  for (const auto& b : boots) {
    outfile << format_datetime(b.start_time) << " Boot Start" << std::endl;
    if (b.complete) {
      boost::posix_time::time_duration diff = b.end_time - b.start_time;
      outfile << format_datetime(b.end_time) << " Boot Complete - "
              << diff.total_seconds() << " seconds" << std::endl;
    } else {
      outfile << format_datetime(b.start_time)
              << " Boot Failure - No boot complete before next start or EOF"
              << std::endl;
    }
  }

  std::cout << "Report written to " << output_filename << std::endl;
  return 0;
}
