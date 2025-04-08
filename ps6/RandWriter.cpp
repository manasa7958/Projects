// Copyright Manasa Praveen 2025

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stdexcept>
#include <sstream>
#include <set>
#include <unordered_map>
#include <algorithm> 
#include "RandWriter.hpp"

RandWriter::RandWriter(const std::string& str, size_t k)
    : text(str), k(k), gen(std::mt19937(42)) {
    if (str.length() < k) {
        throw std::invalid_argument("Text length must be at least k");
    }

    std::string circular_text = str + str.substr(0, k);

    if (k == 0) {
        for (char c : str) {
            kgram_map[""][c]++;
            kgram_count[""]++;
            if (alphabet.find(c) == std::string::npos) {
                alphabet += c;
            }
        }
    } else {
        for (size_t i = 0; i < str.size(); ++i) {
            std::string kgram = circular_text.substr(i, k);
            char next_char = circular_text[i + k];

            kgram_map[kgram][next_char]++;
            kgram_count[kgram]++;
            if (alphabet.find(next_char) == std::string::npos) {
                alphabet += next_char;
            }
        }
    }
}

size_t RandWriter::orderK() const {
    return k;
}

int RandWriter::freq(const std::string& kgram) const {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram must be of length k");
    }
    if (k == 0) {
        return static_cast<int>(text.length());
    }

    auto it = kgram_count.find(kgram);
    return (it != kgram_count.end()) ? it->second : 0;
}

int RandWriter::freq(const std::string& kgram, char c) const {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram must be of length k");
    }

    if (k == 0) {
        return static_cast<int>(std::count(text.begin(), text.end(), c));
    }

    auto it = kgram_map.find(kgram);
    if (it == kgram_map.end()) {
        return 0;
    }
    auto cit = it->second.find(c);
    return (cit != it->second.end()) ? cit->second : 0;
}

char RandWriter::kRand(const std::string& kgram) {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram must be of length k");
    }

    std::unordered_map<char, int> dist_map;

    if (k == 0) {
        for (char c : text) {
            dist_map[c]++;
        }
    } else {
        auto it = kgram_map.find(kgram);
        if (it == kgram_map.end()) {
            throw std::invalid_argument("kgram not found");
        }
        dist_map = it->second;
    }

    std::vector<char> chars;
    std::vector<int> weights;

    for (const auto& pair : dist_map) {
        chars.push_back(pair.first);
        weights.push_back(pair.second);
    }

    std::discrete_distribution<> dist(weights.begin(), weights.end());
    return chars[dist(gen)];
}

std::string RandWriter::generate(const std::string& kgram, size_t l) {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram must be of length k");
    }
    if (l < k) {
        throw std::invalid_argument("Length must be at least k");
    }

    std::string result = kgram;
    std::string current = kgram;

    while (result.length() < l) {
        char next = kRand(current);
        result += next;
        if (k > 0) {
            current = result.substr(result.length() - k, k);
        }
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
