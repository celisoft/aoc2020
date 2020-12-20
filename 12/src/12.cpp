#include <fstream>
#include <fmt/core.h>
#include <string>
#include <vector>

void rotateRight(char& pCurrentDir, char& pCurrentDirEW, char& pCurrentDirNS, int pNbMove) {
    for (int nbRot = 0; nbRot < pNbMove; nbRot++) {
        switch (pCurrentDir) {
            case 'E':
                pCurrentDir = 'S';
                pCurrentDirNS = 'S';
                break;
            case 'W':
                pCurrentDir = 'N';
                pCurrentDirNS = 'N';
                break;
            case 'N':
                pCurrentDir = 'E';
                pCurrentDirEW = 'E';
                break;
            case 'S':
                pCurrentDir = 'W';
                pCurrentDirEW = 'W';
                break;
        }
    }
}

void rotateLeft(char& pCurrentDir, char& pCurrentDirEW, char& pCurrentDirNS, int pNbMove){
    for (int nbRot = 0; nbRot < pNbMove; nbRot++) {
        switch (pCurrentDir) {
            case 'E':
                pCurrentDir = 'N';
                pCurrentDirNS = 'N';
                break;
            case 'W':
                pCurrentDir = 'S';
                pCurrentDirNS = 'S';
                break;
            case 'N':
                pCurrentDir = 'W';
                pCurrentDirEW = 'W';
                break;
            case 'S':
                pCurrentDir = 'E';
                pCurrentDirEW = 'E';
                break;
        }
    }
}

void moveForward(char& pCurrentDir, int pDistance, double& pEastWestVal, double& pNorthSouthVal) {
    switch (pCurrentDir) {
        case 'E':
            pEastWestVal += pDistance;
            break;
        case 'W':
            pEastWestVal -= pDistance;
            break;
        case 'N':
            pNorthSouthVal += pDistance;
            break;
        case 'S':
            pNorthSouthVal -= pDistance;
            break;
    }
}

double processPuzzle1(std::vector<std::string>& paInstructions) {
    double northSouthVal = 0;
    double eastWestVal = 0;

    char currentDir = 'E';
    char currentDirEW = 'E';
    char currentDirNS = 'N';

    for (std::string paInstruction : paInstructions) {
        char paChar = paInstruction[0];
        int paVal = std::stoi(paInstruction.substr(1, paInstruction.size() - 1));

        fmt::print("{0}:{1}-{2}\n", paInstruction, paChar, paVal);

        int nbRot = 0;
        switch (paChar) {
            case 'F':
                moveForward(currentDir, paVal, eastWestVal, northSouthVal);
                break;
            case 'R':
                nbRot = abs(paVal / 90);
                rotateRight(currentDir, currentDirEW, currentDirNS, nbRot);
                break;
            case 'L':
                nbRot = abs(paVal / 90);
                rotateLeft(currentDir, currentDirEW, currentDirNS, nbRot);
                break;
            case 'N':
                northSouthVal += paVal;
                break;
            case 'S':
                northSouthVal -= paVal;
                break;
            case 'E':
                eastWestVal += paVal;
                break;
            case 'W':
                eastWestVal -= paVal;
                break;
        }

        fmt::print("{0} {1}, {2} {3}\n", currentDirEW, abs(eastWestVal), currentDirNS, abs(northSouthVal));
    }

    return abs(northSouthVal) + abs(eastWestVal);
}

// TODO Puzzle 2

int main()
{
    fmt::print("Reading file\n");

    std::ifstream inputStream("input.txt");
    std::vector<std::string> dataLines;

    std::string entry;
    while (std::getline(inputStream, entry)) {
        dataLines.push_back(entry);
    }
    inputStream.close();

    double puzzleRes1 = processPuzzle1(dataLines);
    //double puzzleRes2 = processPuzzle2(bagRules);
    fmt::print("------------------------\n");
    fmt::print("Puzzle 1 solution: {0}\n", puzzleRes1);
    //fmt::print("Puzzle 2 solution: {0}", puzzleRes2);

    return 0;
}