#include <algorithm>
#include <fstream>
#include <fmt/core.h>
#include <string>
#include <vector>

std::vector<double> getPreambleSums(std::vector<double>& pDataLines, int pPreambleSize) {
    std::vector<double> controlNumbers;
    for (int controlA = 0; controlA < pPreambleSize; controlA++) {
        fmt::print("A={0}\n", pDataLines[controlA]);
        for (int controlB = 0; controlB < pPreambleSize; controlB++) {
            double sum = pDataLines[controlA] + pDataLines[controlB];
            auto sumSearch = std::find(controlNumbers.begin(), controlNumbers.end(), sum);
            if (sumSearch != controlNumbers.end()) {
                fmt::print("{0} already in sum list\n", sum);
            }
            else {
                fmt::print("{0}+{1}={2} added\n", pDataLines[controlA], pDataLines[controlB], sum);
                controlNumbers.push_back(sum);
            }
        }
    }
    return controlNumbers;
}

double processPuzzle1(std::vector<double>& pDataLines) {
    double res = 0;
    int preambleSize = 25;

    for (int idx = preambleSize; idx < pDataLines.size(); idx++) {
        std::vector<double> currentPreamble;
        std::copy(pDataLines.begin()+idx-preambleSize, pDataLines.begin() + idx, std::back_inserter(currentPreamble));

        std::vector<double> preambleSums = getPreambleSums(currentPreamble, preambleSize);

        auto sumSearch = std::find(preambleSums.begin(), preambleSums.end(), pDataLines[idx]);
        if (sumSearch == preambleSums.end()) {
            fmt::print("{0}\n", pDataLines[idx]);
            res = pDataLines[idx];
            break;
        }
    }

    return res;
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