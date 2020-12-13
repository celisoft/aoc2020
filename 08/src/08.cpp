#include <boost/algorithm/string.hpp>
#include <fstream>
#include <fmt/core.h>
#include <string>
#include <vector>


double processPuzzle1(std::vector<std::string>& pCodeLines) {
    double acc = 0;

    bool eof = false;
    int currentLineNumber = 0;
    int nextLineNumber = 0;

    std::vector<int> executedInstructions;
    while (!eof) {
        std::vector<std::string> currentInstruction;
        boost::split(currentInstruction, pCodeLines[currentLineNumber], [](char delimiter) { return delimiter == ' '; });

        std::string currentKeyword = currentInstruction[0];
        if (currentKeyword == "nop") {
            nextLineNumber = currentLineNumber + 1;
        }
        else if (currentKeyword == "acc") {
            acc += std::stoi(currentInstruction[1]);
            nextLineNumber = currentLineNumber + 1;
        }
        else {
            nextLineNumber = currentLineNumber + std::stoi(currentInstruction[1]);
        }

        executedInstructions.push_back(currentLineNumber);

        if (nextLineNumber < pCodeLines.size()) {
            if (std::find(executedInstructions.begin(), executedInstructions.end(), nextLineNumber) != executedInstructions.end()) {
                eof = true;
            }
            else {
                currentLineNumber = nextLineNumber;
            }
        }
        else {
            eof = true;
        }
    }

    return acc;
}

// TODO Puzzle 2

int main()
{
    fmt::print("Reading file\n");

    std::ifstream inputStream("input.txt");
    std::vector<std::string> codeLines;

    std::string entry;
    while (std::getline(inputStream, entry)) {
        codeLines.push_back(entry);
    }
    inputStream.close();

    double puzzleRes1 = processPuzzle1(codeLines);
    //double puzzleRes2 = processPuzzle2(bagRules);
    fmt::print("------------------------\n");
    fmt::print("Puzzle 1 solution: {0}\n", puzzleRes1);
    //fmt::print("Puzzle 2 solution: {0}", puzzleRes2);

    return 0;
}