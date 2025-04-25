// Copyright 2025 Manasa Praveen

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/regex.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <logfile>\n";
        return 1;
    }

    string input_path = argv[1];
    ifstream infile(input_path);
    if (!infile.is_open()) {
        cerr << "Could not open file: " << input_path << endl;
        return 1;
    }

    boost::regex start_regex(R"((\d{4})-(\d{2})-(\d{2}) (\d{2}):(\d{2}):(\d{2}): \(log\.c\.166\) server started)");
    boost::regex end_regex(R"((\d{4})-(\d{2})-(\d{2}) (\d{2}):(\d{2}):(\d{2})\.(\d{3}):INFO:oejs\.AbstractConnector:Started SelectChannelConnector@0\.0\.0\.0:9080)");
    boost::smatch match;

    ostringstream report;
    int line_number = 1;
    int initiated_count = 0, completed_count = 0;
    bool awaiting = false;
    ptime start_time;

    string line;
    while (getline(infile, line)) {
        if (boost::regex_search(line, match, start_regex)) {
            if (awaiting) {
                report << "**** Incomplete boot ****\n\n";
            }

            date log_date(stoi(match[1]), stoi(match[2]), stoi(match[3]));
            start_time = ptime(log_date, time_duration(stoi(match[4]), stoi(match[5]), stoi(match[6])));

            report << "=== Device boot ===\n";
            report << line_number << "(" << input_path << "): "
                   << to_iso_extended_string(start_time.date()) << ' '
                   << start_time.time_of_day() << " Boot Start\n";

            ++initiated_count;
            awaiting = true;
        } else if (boost::regex_match(line, match, end_regex)) {
            if (awaiting) {
                date log_date(stoi(match[1]), stoi(match[2]), stoi(match[3]));
                ptime end_time(log_date, time_duration(stoi(match[4]), stoi(match[5]), stoi(match[6])));
                time_duration dur = end_time - start_time;

                report << line_number << "(" << input_path << "): "
                       << to_iso_extended_string(end_time.date()) << ' '
                       << end_time.time_of_day() << " Boot Completed\n";
                report << "\tBoot Time: " << dur.total_milliseconds() << "ms\n\n";

                ++completed_count;
                awaiting = false;
            }
        }
        ++line_number;
    }

    if (awaiting) {
        report << "**** Incomplete boot ****\n\n";
    }

    string out_path = input_path + ".rpt";
    ofstream outfile(out_path);
    if (!outfile.is_open()) {
        cerr << "Could not write to file: " << out_path << '\n';
        return 1;
    }

    outfile << "Device Boot Report\n\n";
    outfile << "InTouch log file: " << input_path << '\n';
    outfile << "Lines Scanned: " << line_number - 1 << "\n\n";
    outfile << "Device boot count: initiated = " << initiated_count
            << ", completed: " << completed_count << "\n\n\n";
    outfile << report.str();

    cout << "Report written to " << out_path << endl;
    return 0;
}
