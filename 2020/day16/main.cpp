#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part2-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

struct Rule {
    std::string field;
    std::pair<int, int> range1;
    std::pair<int, int> range2;
    [[nodiscard]] bool applies(const int value) const {
        return aoc::in_range<int>(value, range1.first, range1.second) || aoc::in_range<int>(value, range2.first, range2.second);
    }
};

int main() {
    std::vector<Rule> rules;
    std::vector<std::vector<int>> validTickets;
    std::vector<int> myTicketNumbers;

    {
        aoc::NamedAutoTimer t("part1");

        std::regex reRule(R"((\w.*): (\d+)-(\d+) or (\d+)-(\d+))");

        int invalidNumbersSum = 0;

        aoc::io::loadLinewise(INPUT, [&](const auto& s) {
            std::smatch match;
            if (std::regex_match(s, match, reRule)) {
                rules.push_back({match[1].str(),
                                 {std::stoi(match[2].str()), std::stoi(match[3].str())},
                                 {std::stoi(match[4].str()), std::stoi(match[5].str())}});
            } else if (s.find(',') != std::string::npos) {
                if (myTicketNumbers.empty()) { // first ticket = my own)
                    myTicketNumbers = aoc::tokenizr<int>(s, ',');
                    return;
                }

                auto ticketNumbers = aoc::tokenizr<int>(s, ',');
                bool isValid = true;
                for (const auto& number : ticketNumbers) {
                    // if none of the rules apply, the ticket is invalid
                    if (std::none_of(begin(rules), end(rules), [&](const auto& rule) { return rule.applies(number); })) {
                        invalidNumbersSum += number;
                        isValid = false;
                    }
                }
                if (isValid) validTickets.push_back(ticketNumbers);
            }
        });

        std::cout << "Sum of invalid numbers:" << invalidNumbersSum << std::endl;
        assert(invalidNumbersSum == 19240);
    }

    {
        aoc::NamedAutoTimer t("part2");

        std::map<std::string, std::set<int>> possibilities;
        for (const auto& rule : rules) {
            for (int column = 0; column < validTickets[0].size(); ++column) {
                bool appliesToAllColumns = std::ranges::all_of(validTickets, [&](const auto& ticket) { return rule.applies(ticket[column]); });
                if (appliesToAllColumns) possibilities[rule.field].insert(column);
            }
        }

        long product = 1;

        while (!possibilities.empty()) {
            // find a field that only has ONE possible column
            auto[field, columnSet] = *std::ranges::find_if(possibilities, [](auto& p) { return p.second.size() == 1; });
            int column = *columnSet.begin(); // get the only element in the set
            if (field.starts_with("departure")) product *= myTicketNumbers[column];
            std::erase_if(possibilities, [](auto& p) { return p.second.size() == 1; });
            std::ranges::for_each(possibilities, [&](auto& p) { if (p.second.size() > 1) p.second.erase(column); });
        }

        std::cout << "Product=" << product << std::endl; // not 4213440
        assert(product == 21095351239483);
    }

    return 0;
}

