#include <fstream>
#include <fmt/core.h>
#include <vector>

int processPuzzle1(std::vector<int> pInputNumbers) {
    fmt::print("Processing {0} entries\n", pInputNumbers.size());

    int res1 = 0, res2 = 0;
    for (auto inputNumber1 : pInputNumbers) {
        for (auto inputNumber2 : pInputNumbers) {
            if (inputNumber1 + inputNumber2 == 2020) {
                res1 = inputNumber1;
                res2 = inputNumber2;
                break;
            }
        }
        if (0 != res1) {
            break;
        }
    }

    int finalRes = (res1 * res2);

    fmt::print("End of process\n");
    fmt::print("{0}+{1}=2020\n", res1, res2);
    fmt::print("=> {0}*{1}={2}\n", res1, res2, (res1 * res2));

    return finalRes;
}

int processPuzzle2(std::vector<int> pInputNumbers) {
    fmt::print("Processing {0} entries\n", pInputNumbers.size());

    int res1 = 0, res2 = 0, res3 = 0;
    for (auto inputNumber1 : pInputNumbers) {
        for (auto inputNumber2 : pInputNumbers) {
            for (auto inputNumber3 : pInputNumbers) {
                if (inputNumber1 + inputNumber2 + inputNumber3 == 2020) {
                    res1 = inputNumber1;
                    res2 = inputNumber2;
                    res3 = inputNumber3;
                    break;
                }
            }
            if (0 != res1) {
                break;
            }
        }
        if (0 != res1) {
            break;
        }
    }

    int finalRes = (res1 * res2 * res3);

    fmt::print("End of process\n");
    fmt::print("{0}+{1}+{2}=2020\n", res1, res2, res3);
    fmt::print("=> {0}*{1}*{2}={3}\n", res1, res2, res3, finalRes);

    return finalRes;
}

int main()
{
    fmt::print("Reading file\n");

    std::ifstream inputStream("input.txt");
    std::istream_iterator<int> start(inputStream), end;
    std::vector<int> inputNumbers(start, end);

    int puzzleRes1 = processPuzzle1(inputNumbers);
    int puzzleRes2 = processPuzzle2(inputNumbers);

    fmt::print("------------------------------\n");
    fmt::print("Puzzle 1 solution: {0}\n", puzzleRes1);
    fmt::print("Puzzle 2 solution: {0}", puzzleRes2);

    return 0;
}
