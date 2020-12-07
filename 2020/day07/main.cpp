#include <aoc.h>

#include <utility>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt" // 32
//#define INPUT INPUT_SRC_DIR"/input-test-part2-1.txt" // 126
#define INPUT INPUT_SRC_DIR"/input.txt"

struct Bag {
    Bag() = default;
    explicit Bag(std::string type) : type(std::move(type)) {}
    std::string type;
    std::map<std::string, int> inner;
    bool operator<(const Bag& rhs) const { return type < rhs.type; }; // required by std::set
};

void findPossibleOuterBags(const std::map<std::string, Bag>& bagRules, std::set<Bag>& possibleOuterBags, const std::string& thisBag) {
    std::set<Bag> set;
    for (const auto&[type, bag] : bagRules) {
        if (bag.inner.contains(thisBag)) {
            set.insert(bag);
            possibleOuterBags.insert(bag);
        }
    }

//    possibleOutermostBags.insert(begin(set), end(set));
    for (const auto& bag : set) findPossibleOuterBags(bagRules, possibleOuterBags, bag.type);
}

void countContainedBags(std::map<std::string, Bag>& rules, int& bags, const std::string& thisBagType) {
    for (const auto&[bagType, count] : rules[thisBagType].inner) {
        bags += count;
        for (int i = 0; i < count; ++i) countContainedBags(rules, bags, bagType);
    }
}

int main() {
    std::map<std::string, Bag> bagRules;
    {
        aoc::NamedAutoTimer t("parsing");

        std::regex container(R"(((\d*)? ?(\w+ \w+)) bag)");
        aoc::io::loadLinewise(INPUT, [&](const auto& line) {
            auto searchStart(line.begin());
            std::smatch match;
            regex_search(searchStart, line.cend(), match, container);

            Bag bag(match[1]); // first match is the outer bag

            // subsequent matches are the inner bags
            while (std::regex_search(searchStart, line.cend(), match, container)) {
                if (match[2] != "") bag.inner[match[3]] = std::stoi(match[2]);
                searchStart = match.suffix().first; // continue at end of match
            }

            bagRules[bag.type] = bag;
        });
    }

    {
        aoc::NamedAutoTimer t("part1");

        std::set<Bag> possibleOuterMostBags;
        findPossibleOuterBags(bagRules, possibleOuterMostBags, "shiny gold");
        std::cout << "Possible outermost bags: " << possibleOuterMostBags.size() << std::endl;

        assert(possibleOuterMostBags.size() == 213);
    }

    {
        aoc::NamedAutoTimer t("part2");

        int totalContainedBags = 0;
        countContainedBags(bagRules, totalContainedBags, "shiny gold");
        std::cout << "Total contained bags: " << totalContainedBags << std::endl;

        assert(totalContainedBags == 38426);
    }

    return 0;
}

