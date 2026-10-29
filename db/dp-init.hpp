#ifndef DP_INIT_HPP
#define DP_INIT_HPP

#include "adj-maker.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

inline const std::vector<std::vector<int>>& GetAdjacencyList() {
    static const std::vector<std::vector<int>> adj = [] {
        std::ifstream dictionary(POOPLE_DICTIONARY_PATH);
        if (!dictionary) {
            throw std::runtime_error("could not open dictionary at " POOPLE_DICTIONARY_PATH);
        }

        std::vector<std::string> words;
        std::string word;
        while (dictionary >> word) {
            words.push_back(word);
        }

        return ValidEdges(words);
    }();

    return adj;
}

inline const std::vector<std::string>& GetVals(){
    static const std::vector<std::string>vals = [] {
        std::ifstream dictionary(POOPLE_DICTIONARY_PATH);
        if (!dictionary) {
            throw std::runtime_error("could not open dictionary at " POOPLE_DICTIONARY_PATH);
        }

        std::vector<std::string> words;
        std::string word;
        while (dictionary >> word) {
            words.push_back(word);
        }
        return words;
    }();
    return vals;
}

// Persists a game-rejected word removal. The caller is responsible for
// protecting required words such as the target.
inline bool RemoveWordFromDictionary(const std::string& rejected_word) {
    std::ifstream dictionary(POOPLE_DICTIONARY_PATH);
    if (!dictionary) {
        throw std::runtime_error("could not open dictionary at " POOPLE_DICTIONARY_PATH);
    }

    std::vector<std::string> retained_words;
    std::string word;
    bool removed = false;
    while (dictionary >> word) {
        if (word == rejected_word) {
            removed = true;
        } else {
            retained_words.push_back(word);
        }
    }
    dictionary.close();

    if (!removed) return false;

    std::ofstream output(POOPLE_DICTIONARY_PATH, std::ios::trunc);
    if (!output) {
        throw std::runtime_error("could not write dictionary at " POOPLE_DICTIONARY_PATH);
    }
    for (const std::string& retained_word : retained_words) {
        output << retained_word << '\n';
    }
    if (!output) {
        throw std::runtime_error("could not finish writing dictionary at " POOPLE_DICTIONARY_PATH);
    }
    return true;
}
#endif
