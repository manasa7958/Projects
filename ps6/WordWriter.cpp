// Copyright Manasa Praveen 2025
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include "WordWriter.hpp"

WordWriter::WordWriter(const std::string& text, size_t k)
    : k(k), gen(42) {

    words = tokenize(text);
    if (words.size() < k) {
        throw std::invalid_argument("Text must contain at least k words");
    }

    std::vector<std::string> circular_words = words;
    circular_words.insert(circular_words.end(), words.begin(), words.begin() + k);

    for (size_t i = 0; i < words.size(); ++i) {
        std::string kgram = "";
        for (size_t j = 0; j < k; ++j) {
            kgram += circular_words[i + j] + (j < k - 1 ? " " : "");
        }
        std::string next_word = circular_words[i + k];
        kgram_map[kgram][next_word]++;
        kgram_count[kgram]++;
        if (std::find(alphabet.begin(), alphabet.end(), next_word) == alphabet.end()) {
            alphabet.push_back(next_word);
        }
    }
}

size_t WordWriter::orderK() const {
    return k;
}

int WordWriter::freq(const std::string& kgram) const {
    auto it = kgram_count.find(kgram);
    return it != kgram_count.end() ? it->second : 0;
}

int WordWriter::freq(const std::string& kgram, const std::string& word) const {
    auto it = kgram_map.find(kgram);
    if (it == kgram_map.end()) return 0;
    auto it2 = it->second.find(word);
    return it2 != it->second.end() ? it2->second : 0;
}

std::string WordWriter::kRand(const std::string& kgram) {
    auto it = kgram_map.find(kgram);
    if (it == kgram_map.end()) {
        throw std::invalid_argument("kgram not found");
    }

    const auto& dist_map = it->second;
    std::vector<std::string> words;
    std::vector<int> weights;
    for (const auto& pair : dist_map) {
        words.push_back(pair.first);
        weights.push_back(pair.second);
    }

    std::discrete_distribution<> dist(weights.begin(), weights.end());
    return words[dist(gen)];
}

std::string WordWriter::generate(const std::string& kgram, size_t L) {
    std::vector<std::string> output;
    std::istringstream iss(kgram);
    std::string word;
    while (iss >> word) output.push_back(word);

    if (output.size() != k) {
        throw std::invalid_argument("kgram must have exactly k words");
    }

    std::string current = kgram;
    for (size_t i = k; i < L; ++i) {
        std::string next = kRand(current);
        output.push_back(next);
        std::ostringstream oss;
        for (size_t j = output.size() - k; j < output.size(); ++j) {
            oss << output[j];
            if (j < output.size() - 1) oss << " ";
        }
        current = oss.str();
    }

    std::ostringstream result;
    for (size_t i = 0; i < output.size(); ++i) {
        result << output[i];
        if (i < output.size() - 1) result << " ";
    }
    return result.str();
}

std::ostream& operator<<(std::ostream& os, const WordWriter& ww) {
    os << "Order: " << ww.k << "\n";
    os << "Alphabet: ";
    for (const auto& word : ww.alphabet) os << word << " ";
    os << "\n";
    for (const auto& pair : ww.kgram_map) {
        os << '"' << pair.first << "" : ";
        for (const auto& freq : pair.second) {
            os << freq.first << " -> " << freq.second << ", ";
        }
        os << "\n";
    }
    return os;
}

std::vector<std::string> WordWriter::tokenize(const std::string& text) const {
    std::istringstream iss(text);
    std::vector<std::string> tokens;
    std::string word;
    while (iss >> word) tokens.push_back(word);
    return tokens;
}
