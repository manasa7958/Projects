// Copyright Manasa Praveen 2025
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;

// Struct to hold a boot event
struct BootEvent {
    int line_number;
    string timestamp_str;
    ptime timestamp;
};

ptime parse_timestamp(const string& ts) {
    // Example: Apr 21 17:37:46 => "%b %d %H:%M:%S"
    stringstream ss(ts);
    ss.imbue(locale(locale::classic(), new time_input_facet("%b %d %H:%M:%S")));
    ptime pt;
    ss >> pt;
    return pt;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./ps7 <input_log_file>" << endl;
        return 1;
    }

    string input_filename = argv[1];
    ifstream infile(input_filename);
    if (!infile.is_open()) {
        cerr << "Error: Cannot open file " << input_filename << endl;
        return 1;
    }

    // Output file: append .rpt
    string output_filename = input_filename + ".rpt";
    ofstream outfile(output_filename);

    regex start_re(R"((\w{3} \d{1,2} \d{2}:\d{2}:\d{2}).*\(log\.c\.166\) server started)");
    regex end_re(R"((\w{3} \d{1,2} \d{2}:\d{2}:\d{2}).*oejs\.AbstractConnector:Started SelectChannelConnector)");

    string line;
    int line_number = 0;
    vector<BootEvent> boots;

    BootEvent current_start;
    bool waiting_for_end = false;

    while (getline(infile, line)) {
        line_number++;
        smatch match;

        if (regex_search(line, match, start_re)) {
            // Found a new start
            if (waiting_for_end) {
                outfile << "Line " << current_start.line_number << ": " << current_start.timestamp_str
                        << " Boot Failure - No boot complete before next start" << endl;
            }

            current_start = {
                line_number,
                match[1],
                parse_timestamp(match[1])
            };
            waiting_for_end = true;

            outfile << "Line " << current_start.line_number << ": " << current_start.timestamp_str << " Boot Start" << endl;
        }
        else if (waiting_for_end && regex_search(line, match, end_re)) {
            // Found end after start
            string end_ts_str = match[1];
            ptime end_time = parse_timestamp(end_ts_str);
            time_duration diff = end_time - current_start.timestamp;

            outfile << "Line " << line_number << ": " << end_ts_str
                    << " Boot Complete - " << diff.total_seconds() << " seconds" << endl;

            waiting_for_end = false;
        }
    }

    if (waiting_for_end) {
        outfile << "Line " << current_start.line_number << ": " << current_start.timestamp_str
                << " Boot Failure - No boot complete before end of file" << endl;
    }

    infile.close();
    outfile.close();

    cout << "Report written to " << output_filename << endl;
    return 0;
}
