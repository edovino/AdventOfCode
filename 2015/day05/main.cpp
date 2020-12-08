#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part2.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

void part1() {
    aoc::NamedAutoTimer t("part 1");

    std::string vowels = "aeiou";
    std::vector<std::string> pairs(26);
    std::generate(pairs.begin(), pairs.end(), [ch = 'a']() mutable {
        std::string chch;
        chch += ch;
        chch += ch;
        ch++;
        return chch;
    });
    std::vector<std::string> forbidden{"ab", "cd", "pq", "xy"};

    int niceCount = 0;
    aoc::io::loadLinewise(INPUT, [&](const auto& s) {
        bool hasThreeVowels = std::count_if(begin(s), end(s), [&](auto& c) { return vowels.find(c) != std::string::npos; }) >= 3;
        if (!hasThreeVowels) return;

        bool hasPair = std::any_of(begin(pairs), end(pairs), [&](auto& pair) { return s.find(pair) != std::string::npos; });
        if (!hasPair) return;

        bool noForbidden = std::none_of(begin(forbidden), end(forbidden), [&](auto& pair) { return s.find(pair) != std::string::npos; });
        if (!noForbidden) return;

        niceCount++;
    });

    std::cout << "Nice count: " << niceCount << std::endl;
    assert(niceCount == 255);
}

void part2() {
    aoc::NamedAutoTimer t("part 2");

    std::regex reDiscretePairs(".*([a-z][a-z]).*\\1.*");
    std::regex reRepeatWithSkip(".*([a-z])[a-z]\\1.*");

    int niceCount = 0;
    aoc::io::loadLinewise(INPUT, [&](auto& s) {
        bool hasDiscretePairs = std::regex_match(s, reDiscretePairs);
        if (!hasDiscretePairs) return;

        bool hasRepeatWithSkip = std::regex_match(s, reRepeatWithSkip);
        if (!hasRepeatWithSkip) return;

        niceCount++;
    });
    std::cout << "Nice count: " << niceCount << std::endl;
    assert(niceCount == 55);
}

int main() {
    part1();
    part2();
    return 0;
}