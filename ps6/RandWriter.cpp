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
    : text(str), k(k), gen(42) {
    if (str.length() < k) {
        throw std::invalid_argument("Text length must be at least k");
    }

    std::string circular_text = str + str.substr(0, k);

    if (k == 0) {
        kgram_count[""] = str.size();
        for (char c : str) {
            kgram_map[""][c]++;
            if (alphabet.find(c) == std::string::npos) {
                alphabet += c;
            }
        }
    } else {
        auto process_kgram = [&](size_t i) {
            std::string kgram = circular_text.substr(i, k);
            char next_char = circular_text[i + k];

            kgram_map[kgram][next_char]++;
            kgram_count[kgram]++;
            if (alphabet.find(next_char) == std::string::npos) {
                alphabet += next_char;
            }
        };

        for (size_t i = 0; i < str.size(); ++i) {
            process_kgram(i);
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
        return static_cast<int>(std::count_if(text.begin(), text.end(), [&](char ch) {
            return ch == c;
        }));
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
        std::for_each(text.begin(), text.end(), [&](char c) {
            dist_map[c]++;
        });
    } else {
        auto it = kgram_map.find(kgram);
        if (it == kgram_map.end()) {
            throw std::invalid_argument("kgram not found");
        }
        dist_map = it->second;
    }

    std::vector<char> chars;
    std::vector<int> weights;

    std::for_each(dist_map.begin(), dist_map.end(), [&](const auto& pair) {
        chars.push_back(pair.first);
        weights.push_back(pair.second);
    });

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

    std::for_each(rw.kgram_map.begin(), rw.kgram_map.end(), [&](const auto& pair) {
        os << "\"" << pair.first << "\" : ";
        std::for_each(pair.second.begin(), pair.second.end(), [&](const auto& freq_pair) {
            os << freq_pair.first << " -> " << freq_pair.second << ", ";
        });
        os << "\n";
    });

    return os;
}
