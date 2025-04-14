// Copyright Manasa Praveen 2025
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <random>
#include <iostream>

class WordWriter {
public:
    WordWriter(const std::string& text, size_t k);

    size_t orderK() const;
    int freq(const std::string& kgram) const;
    int freq(const std::string& kgram, const std::string& word) const;
    std::string kRand(const std::string& kgram);
    std::string generate(const std::string& kgram, size_t L);

    friend std::ostream& operator<<(std::ostream& os, const WordWriter& ww);

private:
    size_t k;
    std::vector<std::string> words;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> kgram_map;
    std::unordered_map<std::string, int> kgram_count;
    std::vector<std::string> alphabet;
    std::mt19937 gen;

    std::vector<std::string> tokenize(const std::string& text) const;
};
