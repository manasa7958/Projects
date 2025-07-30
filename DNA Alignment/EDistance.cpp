// Copyright Manasa Praveen and Ponita Ty 2025
#include <algorithm>
#include <vector>
#include <sstream>
#include <memory>
#include "EDistance.hpp"

EDistance::EDistance(const std::string& s1, const std::string& s2)
    : str1(s1), str2(s2) {
}

int EDistance::penalty(char a, char b) {
    return (a == b) ? 0 : 1;
}

int EDistance::min3(int a, int b, int c) {
    return std::min(a, std::min(b, c));
}

std::vector<int> EDistance::forwardScore(const std::string& s1, const std::string& s2) {
    int m = s1.length();
    int n = s2.length();

    std::vector<int> prev(n + 1);
    std::vector<int> curr(n + 1);

    for (int j = 0; j <= n; j++) {
        prev[j] = j * 2;
    }

    for (int i = 1; i <= m; i++) {
        curr[0] = i * 2;

        for (int j = 1; j <= n; j++) {
            int matchOrMismatch = prev[j-1] + penalty(s1[i-1], s2[j-1]);
            int deleteCost = prev[j] + 2;
            int insertCost = curr[j-1] + 2;
            curr[j] = min3(matchOrMismatch, deleteCost, insertCost);
        }
        prev = curr;
    }

    return prev;
}

std::vector<int> EDistance::reverseScore(const std::string& s1, const std::string& s2) {
    std::string revS1(s1.rbegin(), s1.rend());
    std::string revS2(s2.rbegin(), s2.rend());

    return forwardScore(revS1, revS2);
}

void EDistance::hirschbergAlign(
        const std::string& s1, int start1, int end1,
        const std::string& s2, int start2, int end2,
        std::vector<std::string>& alignmentLines) {
    if (end1 - start1 == 0) {
        for (int j = start2; j < end2; j++) {
            std::ostringstream oss;
            oss << "- " << s2[j] << " 2";
            alignmentLines.push_back(oss.str());
        }
        return;
    } else if (end2 - start2 == 0) {
        for (int i = start1; i < end1; i++) {
            std::ostringstream oss;
            oss << s1[i] << " - 2";
            alignmentLines.push_back(oss.str());
        }
        return;
    } else if (end1 - start1 == 1) {
        if (end2 - start2 == 1) {
            std::ostringstream oss;
            oss << s1[start1] << " " << s2[start2] << " " << penalty(s1[start1], s2[start2]);
            alignmentLines.push_back(oss.str());
        } else {
            int bestJ = start2;
            int bestScore = 2 * (end2 - start2 - 1) + penalty(s1[start1], s2[start2]);
            for (int j = start2 + 1; j < end2; j++) {
                int currentScore = 2 * (j - start2) + penalty(s1[start1],
                s2[j]) + 2 * (end2 - j - 1);
                if (currentScore < bestScore) {
                    bestScore = currentScore;
                    bestJ = j;
                }
            }
            for (int j = start2; j < bestJ; j++) {
                std::ostringstream oss;
                oss << "- " << s2[j] << " 2";
                alignmentLines.push_back(oss.str());
            }
            std::ostringstream oss;
            oss << s1[start1] << " " << s2[bestJ] << " " << penalty(s1[start1], s2[bestJ]);
            alignmentLines.push_back(oss.str());

            for (int j = bestJ + 1; j < end2; j++) {
                std::ostringstream oss;
                oss << "- " << s2[j] << " 2";
                alignmentLines.push_back(oss.str());
            }
        }
        return;
    }
    int mid1 = (start1 + end1) / 2;
    std::string s1FirstHalf = s1.substr(start1, mid1 - start1);
    std::string s2Segment = s2.substr(start2, end2 - start2);
    std::vector<int> scoreL = forwardScore(s1FirstHalf, s2Segment);

    std::string s1SecondHalf = s1.substr(mid1, end1 - mid1);
    std::vector<int> scoreR = reverseScore(s1SecondHalf, s2Segment);

    int mid2 = start2;
    int bestScore = scoreL[0] + scoreR[end2 - start2];

    for (int j = 1; j <= end2 - start2; j++) {
        int currentScore = scoreL[j] + scoreR[end2 - start2 - j];
        if (currentScore < bestScore) {
            bestScore = currentScore;
            mid2 = start2 + j;
        }
    }

    hirschbergAlign(s1, start1, mid1, s2, start2, mid2, alignmentLines);
    hirschbergAlign(s1, mid1, end1, s2, mid2, end2, alignmentLines);
}

int EDistance::optDistance() {
    if (str1.empty()) return str2.length() * 2;
    if (str2.empty()) return str1.length() * 2;
    if (str1.length() > 10000 || str2.length() > 10000) {
        std::vector<int> scores = forwardScore(str1, str2);
        return scores[str2.length()];
    }

    int m = str1.length();
    int n = str2.length();

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        dp[i][0] = i * 2;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j * 2;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int matchOrMismatch = dp[i-1][j-1] + penalty(str1[i-1], str2[j-1]);
            int deleteCost = dp[i-1][j] + 2;
            int insertCost = dp[i][j-1] + 2;
            dp[i][j] = min3(matchOrMismatch, deleteCost, insertCost);
        }
    }

    return dp[m][n];
}

std::string EDistance::alignment() {
    if (str1.empty()) {
        std::ostringstream oss;
        for (size_t i = 0; i < str2.length(); i++) {
            oss << "- " << str2[i] << " 2\n";
        }
        std::string result = oss.str();
        return result.empty() ? "" : result.substr(0, result.length() - 1);
    }

    if (str2.empty()) {
        std::ostringstream oss;
        for (size_t i = 0; i < str1.length(); i++) {
            oss << str1[i] << " - 2\n";
        }
        std::string result = oss.str();
        return result.empty() ? "" : result.substr(0, result.length() - 1);
    }

    if (str1.length() > 10000 || str2.length() > 10000) {
        std::vector<std::string> alignmentLines;
        hirschbergAlign(str1, 0, str1.length(), str2, 0, str2.length(), alignmentLines);

        std::ostringstream oss;
        for (const auto& line : alignmentLines) {
            oss << line << "\n";
        }
        std::string result = oss.str();
        return result.empty() ? "" : result.substr(0, result.length() - 1);
    }

    int m = str1.length();
    int n = str2.length();

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        dp[i][0] = i * 2;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j * 2;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int matchOrMismatch = dp[i-1][j-1] + penalty(str1[i-1], str2[j-1]);
            int deleteCost = dp[i-1][j] + 2;
            int insertCost = dp[i][j-1] + 2;
            dp[i][j] = min3(matchOrMismatch, deleteCost, insertCost);
        }
    }

    std::vector<std::string> lines;
    int i = m, j = n;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1] + penalty(str1[i-1], str2[j-1])) {
            std::ostringstream oss;
            oss << str1[i-1] << " " << str2[j-1] << " " << penalty(str1[i-1], str2[j-1]);
            lines.push_back(oss.str());
            i--;
            j--;
        } else if (i > 0 && dp[i][j] == dp[i-1][j] + 2) {
            std::ostringstream oss;
            oss << str1[i-1] << " - 2";
            lines.push_back(oss.str());
            i--;
        } else if (j > 0 && dp[i][j] == dp[i][j-1] + 2) {
            std::ostringstream oss;
            oss << "- " << str2[j-1] << " 2";
            lines.push_back(oss.str());
            j--;
        }
    }

    std::ostringstream oss;
    for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
        oss << *it << "\n";
    }
    std::string result = oss.str();
    return result.empty() ? "" : result.substr(0, result.length() - 1);
}
