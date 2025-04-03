// Copyright Manasa Praveen and Ponita Ty 2025
#pragma once

#include <string>

class EDistance {
 public:
    EDistance(const std::string& s1, const std::string& s2);

    static int penalty(char a, char b);
    static int min3(int a, int b, int c);

    int optDistance();
    std::string alignment();
 private:
};
