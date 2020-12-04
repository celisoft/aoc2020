#include <fstream>
#include <fmt/core.h>
#include <string>
#include <vector>

bool isTree(char pChar) {
    if (pChar == '#') {
        return true;
    }

    return false;
}

int processPuzzle1(std::vector<std::string> pMapLines, int pRightStep, int pDownStep) {
    int treeCpt = 0;
    int colCpt = pRightStep;

    for (int lineCpt = pDownStep; lineCpt < pMapLines.size(); lineCpt += pDownStep) {
        fmt::print("[{0},{1}]={2}", lineCpt, colCpt, pMapLines[lineCpt][colCpt]);
        if (isTree(pMapLines[lineCpt][colCpt])) {
            treeCpt++;
        }

        colCpt += pRightStep;
    }
    fmt::print("\n---\n");
    return treeCpt;
}

long long processPuzzle2(std::vector<std::string> pMapLines) {
    long long treeCpt = processPuzzle1(pMapLines, 1, 1);
    treeCpt *= processPuzzle1(pMapLines, 3, 1);
    treeCpt *= processPuzzle1(pMapLines, 5, 1);
    treeCpt *= processPuzzle1(pMapLines, 7, 1);
    treeCpt *= processPuzzle1(pMapLines, 1, 2);

    return treeCpt;
}

int analyzeFile(std::string pFilename, int pMaxRightStep) {
    std::ifstream inputStream("input.txt");
    std::string mapLine;

    std::getline(inputStream, mapLine);
    int lineSize = mapLine.size();
    
    int lineCpt = 1;
    while (std::getline(inputStream, mapLine)) {
        lineCpt++;
    }
    inputStream.close();

    int xFactor = 1;
    while ((lineSize*xFactor) < (pMaxRightStep*lineCpt)) {
        xFactor++;
    }

    return xFactor;
}

int main()
{
    fmt::print("Reading file\n");

    int xFactor = analyzeFile("input.txt", 7);
    fmt::print("Factor={0}\n", xFactor);

    std::ifstream inputStream("input.txt");
    std::vector<std::string> mapLines;

    std::string mapLine;
    while (std::getline(inputStream, mapLine)) {
        std::string increasedMapLine;
        for (int factor = 0; factor < xFactor; factor++) {
            increasedMapLine += mapLine;
        }

        mapLines.push_back(increasedMapLine);
    }

    inputStream.close();

    int puzzleRes1 = processPuzzle1(mapLines, 3, 1);
    long long puzzleRes2 = processPuzzle2(mapLines);

    fmt::print("Puzzle 1 solution: {0}\n", puzzleRes1);
    fmt::print("Puzzle 2 solution: {0}", puzzleRes2);

    return 0;
}