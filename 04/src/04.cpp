#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <fmt/core.h>
#include <functional>
#include <regex>
#include <string>
#include <vector>

bool isPassportContains(std::string pPassport, std::string pField) {
    auto searchRes = std::search(pPassport.begin(), pPassport.end(),
        std::boyer_moore_searcher(pField.begin(), pField.end()));
    if (searchRes != pPassport.end()) {
        return true;
    }
    return false;
}

/**
* Required fields :
*     byr(Birth Year)
*     iyr(Issue Year)
*     eyr(Expiration Year)
*     hgt(Height)
*     hcl(Hair Color)
*     ecl(Eye Color)
*     pid(Passport ID)
*  Other :
*     cid (Country ID)
**/
bool isPassportComplete(std::string pPassport) {
    if (isPassportContains(pPassport, "byr:") && isPassportContains(pPassport, "iyr:")
        && isPassportContains(pPassport, "eyr:") && isPassportContains(pPassport, "hgt:")
        && isPassportContains(pPassport, "hcl:") && isPassportContains(pPassport, "ecl:")
        && isPassportContains(pPassport, "pid:")) {
        return true;
    }
    return false;
}

int processPuzzle1(std::vector<std::string> pPassports) {
    int validCpt = 0;
    for (std::string passport : pPassports) {
        fmt::print("Passport {0}\n", passport);
        if (isPassportComplete(passport)) {
            // TODO validate fields
            validCpt++;
        }
    }
    return validCpt;
}

bool isPassportFieldValid(std::string pPassportFieldName, std::string pPassportFieldValue) {
    if ("byr" == pPassportFieldName) {
        // byr(Birth Year) : 1920 => 2002.
        int byrVal = std::stoi(pPassportFieldValue);
        if (byrVal >= 1920 && byrVal <= 2002) {
            return true;
        }
        return false;
    } else if ("iyr" == pPassportFieldName) {
        // iyr(Issue Year) : 2010 => 2020.
        int iyrVal = std::stoi(pPassportFieldValue);
        if (iyrVal >= 2010 && iyrVal <= 2020) {
            return true;
        }
        return false;
    } else if ("eyr" == pPassportFieldName) {
        // eyr(Expiration Year) : 2020 => 2030.
        int eyrVal = std::stoi(pPassportFieldValue);
        if (eyrVal >= 2020 && eyrVal <= 2030) {
            return true;
        }
        return false;
    } else if ("hgt" == pPassportFieldName) {
        // hgt(Height) : cm or in
        auto cmRegex = std::regex("cm");
        auto inRegex = std::regex("in");
        if (std::regex_search(pPassportFieldValue, cmRegex)) {
            // If cm 150 => 193
            int hgtVal = std::stoi(pPassportFieldValue.substr(0, pPassportFieldValue.size() - 2));
            if (hgtVal >= 150 && hgtVal <= 193) {
                return true;
            }
        }
        else if ((std::regex_search(pPassportFieldValue, inRegex))) {
            // If in 59 => 76
            int hgtVal = std::stoi(pPassportFieldValue.substr(0, pPassportFieldValue.size() - 2));
            if (hgtVal >= 59 && hgtVal <= 76) {
                return true;
            }
        }
        return false;
    }
    else if ("hcl" == pPassportFieldName) {
        // hcl(Hair Color) : a # followed by exactly six characters 0-9 or a-f.
        auto pidRegex = std::regex("^#[a-fA-F0-9]{6,6}$");
        if ((std::regex_search(pPassportFieldValue, pidRegex))) {
            return true;
        }
        else {
            fmt::print("Invalid hairs {0}", pPassportFieldValue);
        }
        return false;
        return true;
    }
    else if ("ecl" == pPassportFieldName) {
        // ecl(Eye Color) : exactly one of: amb blu brn gry grn hzl oth
        auto eyeRegex = std::regex("(amb|blu|brn|gry|grn|hzl|oth)");
        if ((std::regex_search(pPassportFieldValue, eyeRegex))) {
            return true;
        }
        return false;
    }
    else if ("pid" == pPassportFieldName) {
        // pid(Passport ID) : a nine-digit number, including leading zeroes.
        auto pidRegex = std::regex("^[0-9]{9,9}$");
        if ((std::regex_search(pPassportFieldValue, pidRegex))) {
            return true;
        }
        return false;
    }

    return true;
}

int processPuzzle2(std::vector<std::string> pPassports) {
    int validCpt = 0;
    for (std::string passport : pPassports) {
        boost::trim(passport);
        fmt::print("Passport {0}\n", passport);

        if (isPassportComplete(passport)) {
            std::vector<std::string> passportFields;
            boost::split(passportFields, passport, [](char delimiter) { return delimiter == ' '; });
            
            int invalidFieldCpt = 0;
            for (std::string passportField : passportFields) {
                std::vector<std::string> passportFieldKeyValue;
                boost::split(passportFieldKeyValue, passportField, [](char delimiter) { return delimiter == ':'; });

                fmt::print("\t-{0}={1}\n", passportFieldKeyValue[0], passportFieldKeyValue[1]);

                if (!isPassportFieldValid(passportFieldKeyValue[0], passportFieldKeyValue[1])) {
                    invalidFieldCpt++;
                }
            }

            if (0 == invalidFieldCpt) {
                validCpt++;
            }
        }
    }
    return validCpt;
}

int main()
{
    fmt::print("Reading file\n");

    std::ifstream inputStream("input.txt");
    std::vector<std::string> passports;

    std::string passportLine;
    std::string currentPassportInfos;

    while (std::getline(inputStream, passportLine)) {
        if (passportLine.empty()) {
            passports.push_back(currentPassportInfos);
            currentPassportInfos = "";
        }
        else {
            currentPassportInfos += " " + passportLine;
        }
    }
    passports.push_back(currentPassportInfos);

    inputStream.close();

    int puzzleRes1 = processPuzzle1(passports);
    int puzzleRes2 = processPuzzle2(passports);
    fmt::print("------------------------\n");
    fmt::print("Puzzle 1 solution: {0}\n", puzzleRes1);
    fmt::print("Puzzle 2 solution: {0}", puzzleRes2);

    return 0;
}