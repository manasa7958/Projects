// Copyright Manasa Praveen 2025

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>
#include <cstdint>
#include <map>
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

std::string extract_date(const boost::posix_time::ptime& pt) {
  return boost::gregorian::to_iso_extended_string(pt.date());
}

std::string extract_time(const boost::posix_time::ptime& pt) {
  std::ostringstream oss;
  oss << std::setw(2) << std::setfill('0') << pt.time_of_day().hours() << ":"
      << std::setw(2) << std::setfill('0') << pt.time_of_day().minutes() << ":"
      << std::setw(2) << std::setfill('0') << pt.time_of_day().seconds();
  return oss.str();
}

int infer_year_from_filename(const std::string& filename) {
  // device3_intouch.log → 2014, device4 → 2013, etc.
  std::regex dev_re(R"(device(\d+)_intouch\.log)");
  std::smatch match;
  if (std::regex_search(filename, match, dev_re)) {
    int dev_num = std::stoi(match[1]);
    if (dev_num == 4) return 2013;
    return 2014;
  }
  return 2014;  // fallback
}

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

  const int year = infer_year_from_filename(input_filename);

  std::regex start_re(
      R"((\w{3} +\d{1,2} \d{2}:\d{2}:\d{2}).*\(log\.c\.166\) server started)");
  std::regex end_re(
      R"((\w{3} +\d{1,2} \d{2}:\d{2}:\d{2}).*oejs\.AbstractConnector:Started SelectChannelConnector)");

  std::string line;
  int line_number = 0;
  boost::posix_time::ptime start_time;
  bool waiting_for_end = false;

  while (std::getline(infile, line)) {
    ++line_number;
    std::smatch match;

    if (std::regex_search(line, match, start_re)) {
      if (waiting_for_end) {
        // previous boot failed – ignore
        waiting_for_end = false;
      }
      start_time = parse_timestamp(match[1], year);
      waiting_for_end = true;
    } else if (waiting_for_end && std::regex_search(line, match, end_re)) {
      boost::posix_time::ptime end_time = parse_timestamp(match[1], year);
      boost::posix_time::time_duration dur = end_time - start_time;

      std::cout << extract_date(start_time) << std::endl;
      std::cout << extract_time(start_time) << std::endl;
      std::cout << extract_date(end_time) << std::endl;
      std::cout << extract_time(end_time) << std::endl;
      std::cout << dur.total_seconds() << std::endl;

      waiting_for_end = false;
    }
  }

  return 0;
}
