#include <algorithm>
#include <cmath>
#include <fstream>
#include <fmt/core.h>
#include <regex>
#include <string>
#include <vector>

double getRowId(std::string pBoardingPass) {
    double minRow = 0;
    double maxRow = 127;

    for (auto i = 0; i < 7; i++) {
        double lowerHalf = round(minRow / 2);
        double upperHalf = round(maxRow / 2);
        if (pBoardingPass[i] == 'F') {
            maxRow = upperHalf + lowerHalf - 1;
        }
        else {
            minRow = upperHalf + lowerHalf;
        }
    }

    return minRow;
}

double getColId(std::string pBoardingPass) {
    double minCol = 0;
    double maxCol = 7;

    for (auto i = 7; i < 10; i++) {
        double lowerHalf = round(minCol / 2);
        double upperHalf = round(maxCol / 2);
        if (pBoardingPass[i] == 'L') {
            maxCol = upperHalf + lowerHalf - 1;
        }
        else {
            minCol = upperHalf + lowerHalf;
        }
    }

    return minCol;
}

double processPuzzle1(std::vector<std::string> pBoardingPasses) {
    std::vector<double> seatIds;
    for (std::string boardingPass : pBoardingPasses) {
        fmt::print("Boarding pass {0}\n", boardingPass);

        double row = getRowId(boardingPass);
        double col = getColId(boardingPass);

        seatIds.push_back((8 * row + col));

    }
    return *max_element(seatIds.begin(), seatIds.end());
}

double processPuzzle2(std::vector<std::string> pBoardingPasses) {
    std::vector<double> seatIds;
    for (std::string boardingPass : pBoardingPasses) {
        fmt::print("Boarding pass {0}\n", boardingPass);

        double row = getRowId(boardingPass);
        double col = getColId(boardingPass);

        seatIds.push_back((8 * row + col));

    }

    std::sort(seatIds.begin(), seatIds.end());

    double seatId = 0;
    int seatIdx = 0;
    int potentialMissingSeatId = 1;

    while (seatId == 0 && potentialMissingSeatId != (seatIds.back() + 1)) {
        fmt::print("SeatId {0}\n", seatIds[seatIdx]);

        if (seatIds[seatIdx] + 1 != seatIds[potentialMissingSeatId]) {
            seatId = seatIds[seatIdx] + 1;
        }

        seatIdx++;
        potentialMissingSeatId++;
    }

    return seatId;
}

int main()
{
    fmt::print("Reading file\n");

    std::ifstream inputStream("input.txt");
    std::vector<std::string> boardingPasses;

    std::string entry;
    while (std::getline(inputStream, entry)) {
        boardingPasses.push_back(entry);
    }
    inputStream.close();

    double puzzleRes1 = processPuzzle1(boardingPasses);
    double puzzleRes2 = processPuzzle2(boardingPasses);
    fmt::print("------------------------\n");
    fmt::print("Puzzle 1 solution: {0}\n", puzzleRes1);
    fmt::print("Puzzle 2 solution: {0}", puzzleRes2);

    return 0;
}