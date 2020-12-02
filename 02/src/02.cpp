#include <boost/algorithm/string.hpp>
#include <fstream>
#include <fmt/core.h>
#include <string>
#include <sstream>
#include <vector>

bool checkPassword(int pMin, int pMax, char pChar, std::string pPassword) {
    int charOccurCpt = 0;
    for (char const& currentPassLetter : pPassword) {
        if (pChar == currentPassLetter) {
            charOccurCpt++;
        }
    }

    if (charOccurCpt >= pMin && charOccurCpt <= pMax) {
        return true;
    }

    return false;
}

int processPuzzle1(std::vector<std::string> pInputEntries) {
    fmt::print("Processing {0} entries\n", pInputEntries.size());

    int validPasswordCpt = 0;
    for (std::string inputEntry : pInputEntries) {
        // std::istringstream entryStream(inputEntry);
        //std::vector<std::string> splittedEntry(std::istream_iterator<std::string>{entryStream},
        //    std::istream_iterator<std::string>());
        std::vector<std::string> splittedEntry;
        boost::split(splittedEntry, inputEntry, [](char delimiter) { return delimiter == ' '; });
        
        std::vector<std::string> limits;
        boost::split(limits, splittedEntry[0], [](char delimiter) { return delimiter == '-'; });

        int min = std::stoi(limits[0]);
        int max = std::stoi(limits[1]);
        char keyChar = splittedEntry[1][0];

        if (checkPassword(min, max, keyChar, splittedEntry[2])) {
            validPasswordCpt++;
        }
    }

    return validPasswordCpt;
}

bool checkPassword2(int pMin, int pMax, char pChar, std::string pPassword) {
    if (pPassword[pMin] == pChar && pPassword[pMax] == pChar) {
        return false;
    }

    if (pPassword[pMin] != pChar && pPassword[pMax] != pChar) {
        return false;
    }

    return true;
}

int processPuzzle2(std::vector<std::string> pInputEntries) {
    fmt::print("Processing {0} entries\n", pInputEntries.size());

    int validPasswordCpt = 0;
    for (std::string inputEntry : pInputEntries) {
        std::vector<std::string> splittedEntry;
        boost::split(splittedEntry, inputEntry, [](char delimiter) { return delimiter == ' '; });

        std::vector<std::string> limits;
        boost::split(limits, splittedEntry[0], [](char delimiter) { return delimiter == '-'; });

        int min = std::stoi(limits[0])-1;
        int max = std::stoi(limits[1])-1;
        char keyChar = splittedEntry[1][0];

        if (checkPassword2(min, max, keyChar, splittedEntry[2])) {
            validPasswordCpt++;
        }
    }

    return validPasswordCpt;
}

int main()
{
    fmt::print("Reading file\n");

    std::ifstream inputStream("input.txt");
    std::vector<std::string> inputEntries;

    std::string entry;
    while (std::getline(inputStream, entry)){
        inputEntries.push_back(entry);
    }    
    
    inputStream.close();

    int puzzleRes1 = processPuzzle1(inputEntries);
    int puzzleRes2 = processPuzzle2(inputEntries);

    fmt::print("------------------------------\n");
    fmt::print("Puzzle 1 solution: {0}\n", puzzleRes1);
    fmt::print("Puzzle 2 solution: {0}", puzzleRes2);

    return 0;
}