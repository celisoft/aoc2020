#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <fmt/core.h>
#include <map>
#include <set>
#include <string>
#include <vector>

void initBagColorsMap(std::vector<std::string>& pBagRules, std::map <std::string, std::map<std::string, int>>& pBagColors) {
    for (std::string bagRule : pBagRules) {
        fmt::print("Bag rule {0}\n", bagRule);

        std::vector<std::string> ruleWords;
        boost::split(ruleWords, bagRule, [](char delimiter) { return delimiter == ' '; });

        std::string keyColor = ruleWords[0] + " " + ruleWords[1];

        fmt::print("Bag with color {0}:\n", keyColor);

        std::map<std::string, int> associatedBagColors;
        if (ruleWords[4] != "no") {
            for (int w = 4; w < ruleWords.size(); w += 4) {
                int bagQty = std::stoi(ruleWords[w]);
                int colorMin = w + 1;
                int colorMax = w + 2;
                if (colorMax < ruleWords.size()) {
                    std::string containedBagColor = ruleWords[colorMin] + " " + ruleWords[colorMax];
                    associatedBagColors.insert(std::pair<std::string, int>(containedBagColor, bagQty));

                    fmt::print("\tThis bag can contain {0} {1} bags\n", bagQty, containedBagColor);
                }
            }
            pBagColors.insert(std::pair<std::string, std::map<std::string, int>>(keyColor, associatedBagColors));
        }
        else {
            fmt::print("\tNo other bag in this bag !\n");
        }
    }
}

bool canContainShinyGoldBag(std::pair<std::string, std::map<std::string, int>> pKeyColor, std::map <std::string, std::map<std::string, int>>& pBagColors) {
    bool canContainShinyBag = false;
    for (std::pair<std::string, int> associatedColors : pKeyColor.second) {
        if (associatedColors.first == "shiny gold") {
            return true;
        }
        else {
            auto colorSearch = pBagColors.find(associatedColors.first);
            if (colorSearch != pBagColors.end()) {
                std::pair<std::string, std::map<std::string, int>> foundColor(colorSearch->first, colorSearch->second);
                if (canContainShinyGoldBag(foundColor, pBagColors)) {
                    return true;
                }
            }
        }
    }
    return canContainShinyBag;
}

double processPuzzle1(std::vector<std::string>& pBagRules) {
    double shinyCpt = 0;

    std::map <std::string, std::map<std::string, int>> bagColorsMap;
    initBagColorsMap(pBagRules, bagColorsMap);

    for (std::pair<std::string, std::map<std::string, int>> currentBagColor : bagColorsMap) {
        if (canContainShinyGoldBag(currentBagColor, bagColorsMap)) {
            shinyCpt++;
        }
    }

    return shinyCpt;
}

// TODO Puzzle 2

int main()
{
    fmt::print("Reading file\n");

    std::ifstream inputStream("input.txt");
    std::vector<std::string> bagRules;

    std::string entry;
    while (std::getline(inputStream, entry)) {
        bagRules.push_back(entry);
    }
    inputStream.close();

    double puzzleRes1 = processPuzzle1(bagRules);
    //double puzzleRes2 = processPuzzle2(bagRules);
    fmt::print("------------------------\n");
    fmt::print("Puzzle 1 solution: {0}\n", puzzleRes1);
    //fmt::print("Puzzle 2 solution: {0}", puzzleRes2);

    return 0;
}