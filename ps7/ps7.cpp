// Copyright Manasa Praveen 2025
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

struct BootEntry {
    int startLine;
    string startTimestamp;
    int endLine;
    string endTimestamp;
    bool success;
};

ptime parse_timestamp(const string& line) {
    static const regex timestamp_pattern(R"((\w{3}\s+\d{1,2}\s\d{2}:\d{2}:\d{2}))");
    smatch match;
    if (regex_search(line, match, timestamp_pattern)) {
        string timestamp = match.str(1);
        stringstream ss("2013 " + timestamp); // Year fixed from the context
        tm t{};
        ss >> get_time(&t, "%Y %b %d %H:%M:%S");
        if (!ss.fail()) {
            return ptime_from_tm(t);
        }
    }
    return ptime(not_a_date_time);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./ps7 <logfile>\n";
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "Could not open file: " << argv[1] << endl;
        return 1;
    }

    string line;
    int lineNum = 0;
    vector<BootEntry> entries;
    BootEntry current = {-1, "", -1, "", false};

    const regex start_pattern(R"(server started)");
    const regex end_pattern(R"(oejs\.AbstractConnector:Started SelectChannelConnector)");

    while (getline(infile, line)) {
        ++lineNum;
        if (regex_search(line, start_pattern)) {
            if (current.startLine != -1 && !current.success) {
                // Last boot failed
                entries.push_back(current);
            }
            current = {lineNum, line, -1, "", false};
        } else if (regex_search(line, end_pattern)) {
            if (current.startLine != -1 && !current.success) {
                current.endLine = lineNum;
                current.endTimestamp = line;
                current.success = true;
                entries.push_back(current);
                current = {-1, "", -1, "", false};
            }
        }
    }

    if (current.startLine != -1 && !current.success) {
        entries.push_back(current);
    }

    string outName = string(argv[1]) + ".rpt";
    ofstream outfile(outName);

    for (const auto& entry : entries) {
        outfile << entry.startLine << " " << entry.startTimestamp << " Boot Start\n";
        if (entry.success) {
            ptime t1 = parse_timestamp(entry.startTimestamp);
            ptime t2 = parse_timestamp(entry.endTimestamp);
            time_duration duration = t2 - t1;
            outfile << entry.endLine << " " << entry.endTimestamp << " Boot Complete: " << duration.total_seconds() << " seconds\n";
        } else {
            outfile << "Boot Failure\n";
        }
    }

    return 0;
}
