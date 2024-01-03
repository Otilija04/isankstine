#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cctype>
#include <algorithm>
#include "lib.h"

int main() {
    std::ifstream inputFile("niujorkas.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::map<std::string, std::pair<int, std::vector<int>>> wordOccurrences;

    std::string word;
    int lineNumber = 1;
    while (inputFile >> word) {
        word = removePunctuation(word);
        if (!word.empty()) {
            auto& entry = wordOccurrences[word];
            entry.first++;  
            entry.second.push_back(lineNumber);
        }
        if (inputFile.peek() == '\n') {
            lineNumber++;
        }
    }

    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string fileContent = buffer.str();

    std::vector<std::string> urls = extractURLs(fileContent);

    inputFile.close();

    std::ofstream outputFile("outputas.txt");

    if (!outputFile.is_open()) {
        std::cerr << "Error opening the output file." << std::endl;
        return 1;
    }

    for (const auto& entry : wordOccurrences) {
        if (entry.second.first > 1) {
            outputFile << entry.first << ": " << entry.second.first << " kartai, eilutes ";
            const auto& occurrences = entry.second.second;
            for (size_t i = 0; i < occurrences.size(); ++i) {
                outputFile << occurrences[i];
                if (i < occurrences.size() - 1) {
                    outputFile << ", ";
                }
            }
            outputFile << std::endl;
        }
    }

    outputFile << "\nURLs tekste:" << std::endl;
    for (const auto& url : urls) {
        outputFile << url << std::endl;
    }

    
    outputFile << "\nZodziai su 'ion':" << std::endl;
    for (const auto& entry : wordOccurrences) {
        if (entry.first.find("ion") != std::string::npos) {
            outputFile << entry.first << std::endl;
        }
    }

    outputFile.close();

    std::cout << "Viskas pavyko. Rezultatai  outputas.txt. faile" << std::endl;

    return 0;
}
