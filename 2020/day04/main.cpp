#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part2-1.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part2-2.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

typedef typename std::map<std::string, std::string> Passport;
typedef typename std::map<std::string, std::function<bool(Passport&)>> ValidationRules;
//typedef typename std::map<std::string, std::function<bool(const Passport&)>> ValidationRules; // hmmm

bool loadPassport(std::istream& s, Passport& passport) {
    bool blankLine = true;
    std::string token;

    while (s >> token) {
        blankLine = false;
        passport[token.substr(0, 3)] = token.substr(4);
    }

    return blankLine;
}

void part1() {
    aoc::NamedAutoTimer t("part1");

    int validCount = 0;
    Passport passport;

    aoc::io::loadLinewiseStringStream(INPUT, [&](auto& s) {
        bool isComplete = loadPassport(s, passport);
        if (!isComplete) return; // keep reading

        if ((passport.size() == 8) || (passport.size() == 7 && !passport.contains("cid"))) ++validCount;
        passport.clear();
    });

    std::cout << "Valid:" << validCount << std::endl;
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    // lambda,lambda chachacha
    ValidationRules rules = {
            {"cid", [](Passport& p) { return true; }},
            {"byr", [](Passport& p) { return p.contains("byr") && aoc::in_range(std::stoi(p["byr"]), 1920, 2002); }},
            {"iyr", [](Passport& p) { return p.contains("iyr") && aoc::in_range(std::stoi(p["iyr"]), 2010, 2020); }},
            {"eyr", [](Passport& p) { return p.contains("eyr") && aoc::in_range(std::stoi(p["eyr"]), 2020, 2030); }},
            {"ecl", [](Passport& p) { return std::string("amb blu brn gry grn hzl oth").find(p["ecl"]) != std::string::npos; }},
            {"hcl", [](Passport& p) { return std::regex_match(p["hcl"], std::regex("#[0-9a-f]{6}")); }},
            {"pid", [](Passport& p) { return std::regex_match(p["pid"], std::regex("[0-9]{9}")); }},
            {"hgt", [](Passport& p) {
                std::smatch match;
                std::regex_match(p["hgt"], match, std::regex("^([0-9]*)(cm|in)$"));
                if (match.empty()) return false;

                if (match[2] == "in") {
                    return aoc::between(std::stoi(match[1]), 59 - 1, 76 + 1);
                } else {
                    return aoc::between(std::stoi(match[1]), 150 - 1, 193 + 1);
                }
            }}
    };

    int valid = 0;
    Passport passport;
    aoc::io::loadLinewiseStringStream(INPUT, [&](auto& s) {
        bool isComplete = loadPassport(s, passport);
        if (!isComplete) return; // keep reading

        if (std::all_of(begin(rules), end(rules), [&](const auto& p) {
            const auto&[token, rule] = p;
            return std::invoke(rule, passport);
        }))
            ++valid;
        passport.clear();
    });

    std::cout << "Valid:" << valid << std::endl;
}

int main() {
    part1(); // 260
    part2(); // 153

    return 0;
}

