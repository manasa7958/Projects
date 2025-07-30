// Copyright 2025 Manasa Praveen
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/regex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

using boost::gregorian::date;
using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::posix_time::to_iso_extended_string;

struct BootState {
    bool isBootOngoing = false;
    ptime bootStartTime;
    int bootStartLine = -1;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <logfile>\n";
        return 1;
    }

    const std::string inputPath = argv[1];
    std::ifstream logFile(inputPath);
    if (!logFile.is_open()) {
        std::cerr << "Error: Cannot open input file " << inputPath << std::endl;
        return 1;
    }

    const boost::regex startPattern(R"((\d{4})-(\d{2})-(\d{2}) (\d{2}):(\d{2}):(\d{2}): \(log\.c\.166\) server started)");
    const boost::regex endPattern(R"((\d{4})-(\d{2})-(\d{2}) (\d{2}):(\d{2}):(\d{2})\.(\d{3}):INFO:oejs\.AbstractConnector:Started SelectChannelConnector@0\.0\.0\.0:9080)");
    boost::smatch match;

    auto buildTimestamp = [](const boost::smatch& m) -> ptime {
        try {
            date d(std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]));
            time_duration t(std::stoi(m[4]), std::stoi(m[5]), std::stoi(m[6]));
            return ptime(d, t);
        } catch (...) {
            return ptime(boost::date_time::not_a_date_time);
        }
    };

    std::ostringstream reportStream;
    BootState boot;
    int currentLine = 0;
    int totalStarts = 0;
    int totalCompletes = 0;
    std::string line;

    while (std::getline(logFile, line)) {
        ++currentLine;

        if (boost::regex_search(line, match, startPattern)) {
            if (boot.isBootOngoing) {
                reportStream << "**** Incomplete boot ****\n\n";
            }

            ptime timestamp = buildTimestamp(match);
            if (timestamp.is_not_a_date_time()) {
                std::cerr << "Warning: Bad start timestamp on line " << currentLine << std::endl;
                continue;
            }

            reportStream << "=== Device boot ===\n";
            reportStream << currentLine << "(" << inputPath << "): "
                         << to_iso_extended_string(timestamp.date()) << " "
                         << timestamp.time_of_day() << " Boot Start\n";

            boot.isBootOngoing = true;
            boot.bootStartTime = timestamp;
            boot.bootStartLine = currentLine;
            ++totalStarts;

        } else if (boost::regex_match(line, match, endPattern) && boot.isBootOngoing) {
            ptime endTimestamp = buildTimestamp(match);
            if (endTimestamp.is_not_a_date_time()) {
                std::cerr << "Warning: Bad end timestamp on line " << currentLine << std::endl;
                continue;
            }

            time_duration duration = endTimestamp - boot.bootStartTime;

            reportStream << currentLine << "(" << inputPath << "): "
                         << to_iso_extended_string(endTimestamp.date()) << " "
                         << endTimestamp.time_of_day() << " Boot Completed\n";
            reportStream << "\tBoot Time: " << duration.total_milliseconds() << "ms\n\n";

            boot.isBootOngoing = false;
            ++totalCompletes;
        }
    }

    if (boot.isBootOngoing) {
        reportStream << "**** Incomplete boot ****\n\n";
    }

    const std::string outputPath = inputPath + ".rpt";
    std::ofstream outputFile(outputPath);
    if (!outputFile) {
        std::cerr << "Error: Could not write report to " << outputPath << std::endl;
        return 1;
    }

    outputFile << "Device Boot Report\n\n";
    outputFile << "InTouch log file: " << inputPath << "\n";
    outputFile << "Lines Scanned: " << currentLine << "\n\n";
    outputFile << "Device boot count: initiated = " << totalStarts
               << ", completed: " << totalCompletes << "\n\n\n";
    outputFile << reportStream.str();

    std::cout << "Report written to " << outputPath << std::endl;
    return 0;
}
