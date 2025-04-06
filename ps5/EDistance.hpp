// Copyright Manasa Praveen and Ponita Ty 2025
#pragma once
#include <string>
#include <vector>

class EDistance {
 public:
    EDistance(const std::string& s1, const std::string& s2);

    static int penalty(char a, char b);
    static int min3(int a, int b, int c);

    int optDistance();
    std::string alignment();

 private:
    std::string str1, str2;

    std::vector<int> forwardScore(const std::string& s1, const std::string& s2);
    std::vector<int> reverseScore(const std::string& s1, const std::string& s2);
    void hirschbergAlign(
        const std::string& s1, int start1, int end1,
        const std::string& s2, int start2, int end2,
        std::vector<std::string>& alignmentLines);
};
