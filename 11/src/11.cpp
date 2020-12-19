#include <algorithm>
#include <fstream>
#include <fmt/core.h>
#include <string>
#include <vector>

double processPuzzle1(std::vector<std::string>& pSeatLines) {
    // [X,Y] : check [X,Y-1], [X,Y+1], [X-1,Y-1], [X-1,Y], [X-1,Y+1], [X+1,Y-1], [X+1,Y] & [X+1,Y+1]
    double seatCpt = 0;
    int roundCpt = 1;
    bool stabilized = false;
    while (!stabilized) {
        fmt::print("Round {0}\n", roundCpt);
        std::vector<std::string> tmpSeatMap = pSeatLines;
        seatCpt = 0;

        for (int x = 0; x < pSeatLines.size(); x++) {
            for (int y = 0; y < pSeatLines[x].size(); y++) {
                char currentSeat = pSeatLines[x][y];
                if (currentSeat == 'L') {
                    if (x == 0) { // First line (x=0)
                        if (y == 0) { // First char : 0,0
                            if (pSeatLines[x][y + 1] != '#' && pSeatLines[x + 1][y] != '#' && pSeatLines[x + 1][y + 1] != '#') {
                                tmpSeatMap[x][y] = '#';
                            }
                        }
                        else if (y == (pSeatLines[x].size() - 1)) { // Last char
                            if (pSeatLines[x][y - 1] != '#' && pSeatLines[x + 1][y - 1] != '#' && pSeatLines[x + 1][y] != '#') {
                                tmpSeatMap[x][y] = '#';
                            }
                        }
                        else if (pSeatLines[x][y - 1] != '#' && pSeatLines[x][y + 1] != '#' &&
                            pSeatLines[x + 1][y - 1] != '#' && pSeatLines[x + 1][y] != '#' && pSeatLines[x + 1][y + 1] != '#') {
                            tmpSeatMap[x][y] = '#';
                        }
                    }
                    else if (x == (pSeatLines.size() - 1)) { // Last line
                        if (y == 0) { // First char
                            if (pSeatLines[x][y + 1] != '#' && pSeatLines[x - 1][y] != '#' && pSeatLines[x - 1][y + 1] != '#') {
                                tmpSeatMap[x][y] = '#';
                            }
                        }
                        else if (y == (pSeatLines[x].size() - 1)) { // Last char
                            if (pSeatLines[x][y - 1] != '#' && pSeatLines[x - 1][y - 1] != '#' && pSeatLines[x - 1][y] != '#') {
                                tmpSeatMap[x][y] = '#';
                            }
                        }
                        else if (pSeatLines[x][y - 1] != '#' && pSeatLines[x][y + 1] != '#' &&
                            pSeatLines[x - 1][y - 1] != '#' && pSeatLines[x - 1][y] != '#' && pSeatLines[x - 1][y + 1] != '#') {
                            tmpSeatMap[x][y] = '#';
                        }
                    }
                    else {
                        if (y == 0) { // First char
                            if (pSeatLines[x][y + 1] != '#' &&
                                pSeatLines[x - 1][y] != '#' && pSeatLines[x - 1][y + 1] != '#' &&
                                pSeatLines[x + 1][y] != '#' && pSeatLines[x + 1][y + 1] != '#') {
                                tmpSeatMap[x][y] = '#';
                            }
                        }
                        else if (y == (pSeatLines[x].size() - 1)) { // Last char
                            if (pSeatLines[x][y - 1] != '#' &&
                                pSeatLines[x - 1][y - 1] != '#' && pSeatLines[x - 1][y] != '#' &&
                                pSeatLines[x + 1][y - 1] != '#' && pSeatLines[x + 1][y] != '#') {
                                tmpSeatMap[x][y] = '#';
                            }
                        }
                        else if (pSeatLines[x][y - 1] != '#' && pSeatLines[x][y + 1] != '#' &&
                            pSeatLines[x - 1][y - 1] != '#' && pSeatLines[x - 1][y] != '#' && pSeatLines[x - 1][y + 1] != '#' &&
                            pSeatLines[x + 1][y - 1] != '#' && pSeatLines[x + 1][y] != '#' && pSeatLines[x + 1][y + 1] != '#') {
                            tmpSeatMap[x][y] = '#';
                        }
                    }
                }
                else if (currentSeat == '#') {
                    int adjacentOccupiedSeatCpt = 0;
                    if (x == 0) { // First line
                        if (y != 0 && y != (pSeatLines[x].size() - 1)) { // Not first char and not last char
                            if (pSeatLines[x][y - 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                            if (pSeatLines[x][y + 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                            if (pSeatLines[x + 1][y - 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                            if (pSeatLines[x + 1][y] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                            if (pSeatLines[x + 1][y + 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                        }
                    }
                    else if (x == (pSeatLines.size() - 1)) {
                        if (y != 0 && y != (pSeatLines[x].size() - 1)) { // Not first char and not last char
                            if (pSeatLines[x][y - 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                            if (pSeatLines[x][y + 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                            if (pSeatLines[x - 1][y - 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                            if (pSeatLines[x - 1][y] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                            if (pSeatLines[x - 1][y + 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                        }
                    }
                    else {
                        if (y != 0) { // Not first char
                            if (pSeatLines[x][y - 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                            if (pSeatLines[x - 1][y - 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                            if (pSeatLines[x + 1][y - 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                        }

                        if (y != (pSeatLines[x].size() - 1)) { // Not last char
                            if (pSeatLines[x][y + 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                            if (pSeatLines[x - 1][y + 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                            if (pSeatLines[x + 1][y + 1] == '#') {
                                adjacentOccupiedSeatCpt++;
                            }
                        }

                        if (pSeatLines[x - 1][y] == '#') {
                            adjacentOccupiedSeatCpt++;
                        }
                        if (pSeatLines[x + 1][y] == '#') {
                            adjacentOccupiedSeatCpt++;
                        }
                    }

                    if (adjacentOccupiedSeatCpt >= 4) {
                        tmpSeatMap[x][y] = 'L';
                    }
                }
            }
        }

        stabilized = std::equal(pSeatLines.begin(), pSeatLines.end(), tmpSeatMap.begin());
        roundCpt++;

        pSeatLines = tmpSeatMap;

        for (int x = 0; x < pSeatLines.size(); x++) {
            for (int y = 0; y < pSeatLines[x].size(); y++) {
                char currentSeat = pSeatLines[x][y];
                if (currentSeat == '#') {
                    seatCpt++;
                }
                fmt::print("{0}", currentSeat);
            }
            fmt::print("\n");
        }
        fmt::print("Seats={0}\n--------------------------\n", seatCpt);
    }

    return seatCpt;
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