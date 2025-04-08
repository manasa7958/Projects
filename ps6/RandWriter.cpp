// Copyright Manasa Praveen 2025

#include <iostream>
#include <random>
#include <stdexcept>
#include <sstream>
#include <set>
#include <unordered_map>
#include "RandWriter.hpp"

RandWriter::RandWriter(const std::string& str, size_t k) : text(str), k(k), gen(std::mt19937(42)) {
    if (str.length() < k) throw std::invalid_argument("Text length must be at least k");

    // Make it circular
    std::string circular_text = str + str.substr(0, k);

    for (size_t i = 0; i < str.size(); ++i) {
        std::string kgram = circular_text.substr(i, k);
        char next_char = circular_text[i + k];

        kgram_count[kgram]++;
        kgram_map[kgram][next_char]++;
        if (alphabet.find(next_char) == std::string::npos)
            alphabet += next_char;
    }
}

size_t RandWriter::orderK() const {
    return k;
}

int RandWriter::freq(const std::string& kgram) const {
    if (kgram.length() != k) throw std::invalid_argument("kgram must be of length k");
    auto it = kgram_count.find(kgram);
    return (it != kgram_count.end()) ? it->second : 0;
}

int RandWriter::freq(const std::string& kgram, char c) const {
    if (kgram.length() != k) throw std::invalid_argument("kgram must be of length k");
    auto it = kgram_map.find(kgram);
    if (it == kgram_map.end()) return 0;
    auto cit = it->second.find(c);
    return (cit != it->second.end()) ? cit->second : 0;
}

char RandWriter::kRand(const std::string& kgram) {
    if (kgram.length() != k) throw std::invalid_argument("kgram must be of length k");
    auto it = kgram_map.find(kgram);
    if (it == kgram_map.end()) throw std::invalid_argument("kgram not found");

    const auto& freq_map = it->second;
    std::vector<char> chars;
    std::vector<int> weights;

    for (const auto& pair : freq_map) {
        chars.push_back(pair.first);
        weights.push_back(pair.second);
    }

    std::discrete_distribution<> dist(weights.begin(), weights.end());
    return chars[dist(gen)];
}

std::string RandWriter::generate(const std::string& kgram, size_t l) {
    if (kgram.length() != k) throw std::invalid_argument("kgram must be of length k");
    if (l < k) throw std::invalid_argument("Length must be at least k");

    std::string result = kgram;
    std::string current = kgram;

    while (result.length() < l) {
        char next = kRand(current);
        result += next;
        current = result.substr(result.length() - k, k);
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const RandWriter& rw) {
    os << "Order: " << rw.k << "\n";
    os << "Alphabet: " << rw.alphabet << "\n";
    for (const auto& pair : rw.kgram_map) {
        os << "\"" << pair.first << "\" : ";
        for (const auto& freq_pair : pair.second) {
            os << freq_pair.first << " -> " << freq_pair.second << ", ";
        }
        os << "\n";
    }
    return os;
}
