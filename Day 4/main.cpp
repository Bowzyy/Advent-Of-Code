#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <cmath>

// split string
std::vector<int> splitIntoNumbers(const std::string& s) {
    std::vector<int> numbers;
    std::string currentNumber;

    for (char c : s) {
        if (std::isdigit(c)) {
            currentNumber += c;
        } else if (!currentNumber.empty()) {
            numbers.push_back(std::stoi(currentNumber));
            currentNumber.clear();
        }
    }

    if (!currentNumber.empty()) {
        numbers.push_back(std::stoi(currentNumber));
    }

    return numbers;
}

int countMatches(const std::string& card) {
    std::vector<int> set1, set2;

    // split card after |
    size_t splitPosition = card.find('|');
    if (splitPosition != std::string::npos) {
        std::string set1_str = card.substr(0, splitPosition);
        std::string set2_str = card.substr(splitPosition + 1);

        set1 = splitIntoNumbers(set1_str);
        set2 = splitIntoNumbers(set2_str);
    }

    // Sort the sets
    std::sort(set1.begin(), set1.end());
    std::sort(set2.begin(), set2.end());

    int matchCount = 0;

    for (int num1 : set1) {
        auto iter = std::find(set2.begin(), set2.end(), num1);
        if (iter != set2.end()) {
            matchCount++;
            set2.erase(iter);  // Remove the matched number from set2
        }
    }

    return matchCount;
}

int main() {
    std::string line;
    std::ifstream file("input.txt");

    int total = 0;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            // std::cout << "Processing line: " << line << std::endl;
            int matches = countMatches(line);
            if (matches >= 1) {
                total += pow(2, matches - 1);
            }
            std::cout << "Number of matches: " << matches << std::endl;
        }
        std::cout << "total: " << total << std::endl;
    }

    return 0;
}
