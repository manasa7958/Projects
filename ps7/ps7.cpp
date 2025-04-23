// Copyright Manasa Praveen 2025
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <map>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

struct BootEvent {
    int lineNumber;
    string timestamp;
    ptime parsedTime;
    bool isStart;
};

struct BootSequence {
    int startLine;
    string startTimestamp;
    ptime startTime;
    int endLine;
    string endTimestamp;
    ptime endTime;
    bool success;
    time_duration duration;
};

ptime parseTimestamp(const string& line) {
    static const regex iso_pattern(R"((\d{4}-\d{2}-\d{2}\s\d{2}:\d{2}:\d{2}))");
    static const regex alt_pattern(R"((\w{3}\s+\d{1,2}\s\d{2}:\d{2}:\d{2}))");
 
    smatch match;

    if (regex_search(line, match, iso_pattern)) {
        string timestamp = match.str(1);
        return time_from_string(timestamp);
    }

    if (regex_search(line, match, alt_pattern)) {
        string timestamp = match.str(1);
        string fullTimestamp = "2013 " + timestamp;

        istringstream ss(fullTimestamp);
        tm t = {};
        ss >> get_time(&t, "%Y %b %d %H:%M:%S");

        if (!ss.fail()) {
            date d(t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);
            time_duration td(t.tm_hour, t.tm_min, t.tm_sec);
            return ptime(d, td);
        }
    }

    return ptime(not_a_date_time);
}

pair<string, string> extractDateAndTime(const string& line) {
    ptime timestamp = parseTimestamp(line);
    if (timestamp.is_not_a_date_time()) {
        return {"Unknown Date", "Unknown Time"};
    }

    string dateStr = to_iso_extended_string(timestamp.date());
    string timeStr = to_simple_string(timestamp.time_of_day());

    return {dateStr, timeStr};
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <logfile>\n";
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "Could not open file: " << argv[1] << endl;
        return 1;
    }

    const regex start_pattern(R"(.*server\sstarted.*)");
    const regex end_pattern(R"(.*oejs\.AbstractConnector:Started\sSelectChannelConnector.*)");

    vector<BootEvent> events;
    string line;
    int lineNum = 0;

    while (getline(infile, line)) {
        lineNum++;

        if (regex_search(line, start_pattern)) {
            ptime timestamp = parseTimestamp(line);
            if (!timestamp.is_not_a_date_time()) {
                events.push_back({lineNum, line, timestamp, true});
            }
        } 
        else if (regex_search(line, end_pattern)) {
            ptime timestamp = parseTimestamp(line);
            if (!timestamp.is_not_a_date_time()) {
                events.push_back({lineNum, line, timestamp, false});
            }
        }
    }

    vector<BootSequence> sequences;
    for (size_t i = 0; i < events.size(); i++) {
        if (events[i].isStart) {
            BootSequence seq;
            seq.startLine = events[i].lineNumber;
            seq.startTimestamp = events[i].timestamp;
            seq.startTime = events[i].parsedTime;
            seq.success = false;

            for (size_t j = i + 1; j < events.size(); j++) {
                if (!events[j].isStart && !seq.success) {
                    seq.endLine = events[j].lineNumber;
                    seq.endTimestamp = events[j].timestamp;
                    seq.endTime = events[j].parsedTime;
                    seq.success = true;
                    seq.duration = seq.endTime - seq.startTime;
                    break;
                } else if (events[j].isStart) {
                    break;
                }
            }
     
            sequences.push_back(seq);
        }
    }

    string outFileName = string(argv[1]) + ".rpt";
    ofstream outfile(outFileName);
    if (!outfile.is_open()) {
        cerr << "Could not create output file: " << outFileName << endl;
        return 1;
    }

    for (const auto& seq : sequences) {
        auto [startDate, startTime] = extractDateAndTime(seq.startTimestamp);

        outfile << seq.startLine << " " << seq.startTimestamp << " Boot Start" << endl;

        if (seq.success) {
            outfile << seq.endLine << " " << seq.endTimestamp << " Boot Complete: " 
                   << seq.duration.total_seconds() << " seconds" << endl;
        } else {
            outfile << "Boot Failure" << endl;
        }
    }

    cout << "Report generated: " << outFileName << endl;
    return 0;
}
