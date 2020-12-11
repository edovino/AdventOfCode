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

        // recursive lambda, cumbersome declaration
        std::function<void(std::set<Bag>&, const std::string&)> findPossibleOuterBags;
        findPossibleOuterBags = [&](std::set<Bag>& possibleOuterBags, const std::string& thisBag) -> void {
            std::set<Bag> set;
            for (const auto&[type, bag] : bagRules) {
                if (bag.inner.contains(thisBag)) {
                    set.insert(bag);
                    possibleOuterBags.insert(bag);
                }
            }

            for (const auto& bag : set) findPossibleOuterBags(possibleOuterBags, bag.type);
        };


        std::set<Bag> possibleOuterMostBags;
        findPossibleOuterBags(possibleOuterMostBags, "shiny gold");
        std::cout << "Possible outermost bags: " << possibleOuterMostBags.size() << std::endl;

        assert(possibleOuterMostBags.size() == 213);
    }

    {
        aoc::NamedAutoTimer t("part2");

        // recursive lambda, cumbersome declaration
        std::function<void(int&, const std::string&)> countContainedBags;
        countContainedBags = [&](int& bags, const std::string& thisBagType) -> void {
            for (const auto&[bagType, count] : bagRules[thisBagType].inner) {
                bags += count;
                for (int i = 0; i < count; ++i) countContainedBags(bags, bagType);
            }
        };

        int totalContainedBags = 0;
        countContainedBags(totalContainedBags, "shiny gold");
        std::cout << "Total contained bags: " << totalContainedBags << std::endl;

        assert(totalContainedBags == 38426);
    }

    return 0;
}

