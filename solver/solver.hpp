#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "../db/dp-init.hpp"

#include <algorithm>
#include <cctype>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

inline std::string NormalizeWord(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(),
        [](unsigned char character) { return static_cast<char>(std::tolower(character)); });
    return value;
}

// Generates one-letter neighbors on demand, so a route can be recalculated
// without words the game has rejected.
inline std::vector<std::string> FindRoute(
    const std::string& start_word,
    const std::unordered_set<std::string>& excluded_words) {
    const std::string start = NormalizeWord(start_word);
    const auto& words = GetVals();
    const std::unordered_set<std::string> dictionary(words.begin(), words.end());
    constexpr char target[] = "poop";

    if (dictionary.find(start) == dictionary.end()) {
        throw std::runtime_error("word is not in this solver's dictionary");
    }
    if (excluded_words.find(start) != excluded_words.end()) {
        throw std::runtime_error("start word has been removed");
    }

    std::queue<std::string> pending;
    std::unordered_map<std::string, std::string> parent;
    parent.emplace(start, start);
    pending.push(start);

    while (!pending.empty() && parent.find(target) == parent.end()) {
        const std::string current = pending.front();
        pending.pop();

        for (std::size_t index = 0; index < current.size(); ++index) {
            // A letter that already matches "poop" is locked in place.
            if (current[index] == target[index]) continue;
            for (char letter = 'a'; letter <= 'z'; ++letter) {
                if (letter == current[index]) continue;
                std::string candidate = current;
                candidate[index] = letter;
                if (dictionary.find(candidate) == dictionary.end() ||
                    excluded_words.find(candidate) != excluded_words.end() ||
                    parent.find(candidate) != parent.end()) {
                    continue;
                }
                parent.emplace(candidate, current);
                pending.push(candidate);
            }
        }
    }

    if (parent.find(target) == parent.end()) {
        throw std::runtime_error("no route remains after the removed words were excluded");
    }

    std::vector<std::string> route;
    for (std::string current = target;; current = parent.at(current)) {
        route.push_back(current);
        if (current == start) break;
    }
    std::reverse(route.begin(), route.end());
    return route;
}
#endif
