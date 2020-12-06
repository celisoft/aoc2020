#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <fmt/core.h>
#include <string>
#include <vector>

double processPuzzle1(std::vector<std::string> pGroupsAnswers) {
    double answersCpt = 0;
    for (std::string groupAnswers : pGroupsAnswers) {
        fmt::print("Group answers {0}\n", groupAnswers);

        std::vector<std::string> individualAnswers;
        boost::split(individualAnswers, groupAnswers, [](char delimiter) { return delimiter == ';'; });

        fmt::print("\tGroup is composed of {0} individual(s)\n", individualAnswers.size());

        std::string filteredGroupAnswers = "";
        for(int i=0; i < individualAnswers.size(); i++) {
            std::string res;

            std::set_difference(individualAnswers[i].begin(), individualAnswers[i].end(),
                filteredGroupAnswers.begin(), filteredGroupAnswers.end(), std::back_inserter(res));
            
            filteredGroupAnswers.insert(filteredGroupAnswers.end(), res.begin(), res.end());
            std::sort(filteredGroupAnswers.begin(), filteredGroupAnswers.end());
        }
        fmt::print("\tUnique answers are: {0} for a total of {1} point(s)\n", filteredGroupAnswers, filteredGroupAnswers.size());
        answersCpt += filteredGroupAnswers.size();
    }
    return answersCpt;
}

double processPuzzle2(std::vector<std::string> pGroupsAnswers) {
    double answersCpt = 0;
    for (std::string groupAnswers : pGroupsAnswers) {
        fmt::print("Group answers {0}\n", groupAnswers);

        std::vector<std::string> individualAnswers;
        boost::split(individualAnswers, groupAnswers, [](char delimiter) { return delimiter == ';'; });

        fmt::print("\tGroup is composed of {0} individual(s)\n", individualAnswers.size());

        std::string filteredGroupAnswers = "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < individualAnswers.size(); i++) {
            std::string res;

            std::set_intersection(individualAnswers[i].begin(), individualAnswers[i].end(),
                filteredGroupAnswers.begin(), filteredGroupAnswers.end(), std::back_inserter(res));

            std::sort(res.begin(), res.end());

            filteredGroupAnswers = res;
        }
        fmt::print("\tCommon answers are: {0} for a total of {1} point(s)\n", filteredGroupAnswers, filteredGroupAnswers.size());
        answersCpt += filteredGroupAnswers.size();
    }
    return answersCpt;
}

int main()
{
    fmt::print("Reading file\n");

    std::ifstream inputStream("input.txt");
    std::vector<std::string> groupsAnswers;

    std::string individualAnswer;
    std::string currentGroupAnswers;
    while (std::getline(inputStream, individualAnswer)) {
        if (individualAnswer.empty()) {
            groupsAnswers.push_back(currentGroupAnswers);
            currentGroupAnswers = "";
        }
        else {
            if (!currentGroupAnswers.empty()) {
                currentGroupAnswers += ";";
            }
            std::sort(individualAnswer.begin(), individualAnswer.end());
            currentGroupAnswers += individualAnswer;
        }
    }
    groupsAnswers.push_back(currentGroupAnswers);
    inputStream.close();

    double puzzleRes1 = processPuzzle1(groupsAnswers);
    double puzzleRes2 = processPuzzle2(groupsAnswers);
    fmt::print("------------------------\n");
    fmt::print("Puzzle 1 solution: {0}\n", puzzleRes1);
    fmt::print("Puzzle 2 solution: {0}", puzzleRes2);

    return 0;
}