#include <algorithm>
#include <fstream>
#include <fmt/core.h>
#include <string>
#include <vector>

double processPuzzle1(std::vector<double>& pDataLines) {
    std::sort(pDataLines.begin(), pDataLines.end());

    double jolt1Cpt = 1;
    double jolt3Cpt = 1;

    for (int joltageIdx = 0; joltageIdx < pDataLines.size()-1; joltageIdx++) {
        double diff = pDataLines[joltageIdx + 1] - pDataLines[joltageIdx];

        if (diff == 1) {
            jolt1Cpt++;
        }
        else if (diff == 3) {
            jolt3Cpt++;
        }

    }

    fmt::print("{0} of 1-jolt differences.\n", jolt1Cpt);
    fmt::print("{0} of 3-jolt differences.\n", jolt3Cpt);

    return jolt1Cpt*jolt3Cpt;
}

// TODO Puzzle 2

int main()
{
    fmt::print("Reading file\n");

    std::ifstream inputStream("input.txt");
    std::vector<double> dataLines;

    std::string entry;
    while (std::getline(inputStream, entry)) {
        dataLines.push_back(std::stod(entry));
    }
    inputStream.close();

    double puzzleRes1 = processPuzzle1(dataLines);
    //double puzzleRes2 = processPuzzle2(bagRules);
    fmt::print("------------------------\n");
    fmt::print("Puzzle 1 solution: {0}\n", puzzleRes1);
    //fmt::print("Puzzle 2 solution: {0}", puzzleRes2);

    return 0;
}