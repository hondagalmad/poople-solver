#ifndef DP_INIT_HPP
#define DP_INIT_HPP

#include "adj-maker.hpp"
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

inline const std::vector<std::vector<int>>& GetAdjacencyList() {
    static const std::vector<std::vector<int>> adj = [] {
        std::ifstream dictionary("dictionary.txt");
        if (!dictionary) {
            throw std::runtime_error("could not open dictionary.txt");
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

#endif
