#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

std::bitset<26> asBits(const std::string& answers) {
    std::bitset<26> bits;
    for (const auto& ch : answers) bits |= 1 << (ch - 'a');
    return bits;
}

void part1() {
    aoc::NamedAutoTimer t("part1");

    int totalUniqueAnswers = 0;

    std::bitset<26> uniqueAnswersPerGroup;
    aoc::io::loadLinewise(INPUT, [&](const auto& line) {
        if (line.length() != 0) {
            uniqueAnswersPerGroup |= asBits(line);
        } else { // blank line, start a new group
            totalUniqueAnswers += uniqueAnswersPerGroup.count();
            uniqueAnswersPerGroup.reset();
        }
    });

//    std::set<char> uniqueAnswersPerGroup;
//    aoc::io::loadLinewise(INPUT, [&](const auto& line) {
//        uniqueAnswersPerGroup.insert(begin(line), end(line));
//        if (line.length() == 0) { // blank line, start a new group
//            totalUniqueAnswers += uniqueAnswersPerGroup.size();
//            uniqueAnswersPerGroup.clear();
//        }
//    });

    std::cout << "Total unique: " << totalUniqueAnswers << std::endl;
    assert(totalUniqueAnswers == 6161);
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    int totalCommonAnswers = 0;
    bool newGroup = true;

    std::bitset<26> commonAnswersPerGroup;
    aoc::io::loadLinewise(INPUT, [&](const auto& line) {
        if (line.length() != 0) {
            if (newGroup) {
                commonAnswersPerGroup = asBits(line);
                newGroup = false;
            } else {
                commonAnswersPerGroup &= asBits(line);
            }
        } else { // blank line, start a new group
            totalCommonAnswers += commonAnswersPerGroup.count();
            commonAnswersPerGroup.reset();
            newGroup = true;
        }
    });

//    bool newGroup = true;
//    std::set<char> commonAnswersPerGroup;
//    aoc::io::loadLinewise(INPUT, [&](const auto& line) {
//        if (line.length() == 0) {
//            newGroup = true;
//            std::cout << commonAnswersPerGroup.size() << std::endl;
//            totalCommonAnswers += commonAnswersPerGroup.size();
//            commonAnswersPerGroup.clear(); // blank line, start a new group
//        } else {
//            if (newGroup) {
//                newGroup = false;
//                commonAnswersPerGroup.insert(begin(line), end(line));
//            } else {
//                for (auto it = commonAnswersPerGroup.begin(); it != commonAnswersPerGroup.end();) {
//                    if (line.find(*it) == std::string::npos) {
//                        it = commonAnswersPerGroup.erase(it);
//                    } else {
//                        ++it;
//                    }
//                }
//            }
//        }
//    });

    std::cout << "Total common answers: " << totalCommonAnswers << std::endl;
    assert(totalCommonAnswers == 2971);
}

int main() {
    part1(); //6161
    part2(); //2971

    return 0;
}

