#include "../solver/solver.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

namespace {

std::string lowercase(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(),
        [](unsigned char character) { return static_cast<char>(std::tolower(character)); });
    return value;
}

void printBanner() {
    std::cout << "\n  P O O P L E   S O L V E R\n"
              << "  Find a valid route from a dictionary word to poop.\n"
              << "  Enter a four-letter word, or q to quit.\n"
              << "  After a route, you can remove a word rejected by the game and refit.\n\n";
}

void printSolution(const std::vector<std::string>& route) {
    std::cout << "\nRoute found in " << route.size() - 1 << " move"
              << (route.size() == 2 ? "" : "s") << ":\n\n";
    for (std::size_t index = 0; index < route.size(); ++index) {
        std::cout << "  " << index << ".  " << route[index];
        if (index + 1 != route.size()) std::cout << "  ->";
        std::cout << '\n';
    }
    std::cout << '\n';
}

} // namespace

int main() {
    printBanner();
    std::string input;
    std::unordered_set<std::string> removed_words;
    while (true) {
        std::cout << "Start word: ";
        if (!std::getline(std::cin, input)) {
            std::cout << "\nGoodbye.\n";
            return 0;
        }
        input = lowercase(input);
        if (input == "q" || input == "quit" || input == "exit") {
            std::cout << "Goodbye.\n";
            return 0;
        }
        if (input.size() != 4) {
            std::cout << "Please enter exactly four letters.\n\n";
            continue;
        }
        if (!std::all_of(input.begin(), input.end(), [](unsigned char character) {
                return std::isalpha(character) != 0;
            })) {
            std::cout << "Please use letters only.\n\n";
            continue;
        }
        try {
            while (true) {
                const std::vector<std::string> route = FindRoute(input, removed_words);
                printSolution(route);

                std::cout << "Rejected game word (Enter for a new start word): ";
                std::string rejected;
                if (!std::getline(std::cin, rejected)) {
                    std::cout << "\nGoodbye.\n";
                    return 0;
                }
                rejected = lowercase(rejected);
                if (rejected.empty()) break;
                if (rejected == "q" || rejected == "quit" || rejected == "exit") {
                    std::cout << "Goodbye.\n";
                    return 0;
                }
                if (rejected == "poop") {
                    std::cout << "The target word cannot be removed.\n\n";
                    continue;
                }
                if (std::find(route.begin(), route.end(), rejected) == route.end()) {
                    std::cout << "That word is not in the displayed route; nothing was removed.\n\n";
                    continue;
                }
                removed_words.insert(rejected);
                RemoveWordFromDictionary(rejected);
                std::cout << "Removed '" << rejected << "' from the dictionary. Refitting route...\n";
            }
        } catch (const std::exception& error) {
            std::cout << "Could not solve '" << input << "': " << error.what() << "\n\n";
        }
    }
}
