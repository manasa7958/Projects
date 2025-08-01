// Copyright Manasa Praveen 2025
#include <iostream>
#include <string>
#include <unordered_map>
#include <random>

class RandWriter {
 public:
    // Create a Markov model of order k from given text
    // Assume that text has length at least k.
    RandWriter(const std::string& str, size_t k);

    size_t orderK() const;  // Order k of Markov model

    // Number of occurences of kgram in text
    // Throw an exception if kgram is not length k
    int freq(const std::string& kgram) const;

    // Number of times that character c follows kgram
    // if order=0, return num of times that char c appears
    // (throw an exception if kgram is not of length k)
    int freq(const std::string& kgram, char c) const;

    // Random character following given kgram
    // (throw an exception if kgram is not of length k)
    // (throw an exception if no such kgram)
    char kRand(const std::string& kgram);

    // Generate a string of length L characters by simulating a trajectory
    // through the corresponding Markov chain. The first k characters of
    // the newly generated string should be the argument kgram.
    // Throw an exception if kgram is not of length k.
    // Assume that L is at least k
    std::string generate(const std::string& kgram, size_t l);

    // Print internal state (order, alphabet, frequencies)
    friend std::ostream& operator<<(std::ostream& os, const RandWriter& rw);

 private:
    std::string text;
    size_t k;
    std::unordered_map<std::string, std::unordered_map<char, int>> kgram_map;
    std::unordered_map<std::string, int> kgram_count;
    std::string alphabet;
    mutable std::mt19937 gen;
};
