#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

int main() {
    std::vector<std::tuple<int, int, int>> presents;

    {
        aoc::NamedAutoTimer t("parse");
        std::regex re(R"((\d*)x(\d*)x(\d*))");
        aoc::io::loadLinewise(INPUT, [&](auto& line) {
            std::smatch match;
            if (std::regex_match(line, match, re) && match.size() == 4) {
                int l = std::stoi(match[1]);
                int w = std::stoi(match[2]);
                int h = std::stoi(match[3]);
                presents.emplace_back(l, w, h);
            }
        });
    }

    {
        aoc::NamedAutoTimer t("part 1");
        int total = 0;

        std::for_each(presents.begin(), presents.end(), [&](auto& present) {
            auto[l, w, h] = present;
            int totalForPresent = 2 * l * w + 2 * w * h + 2 * h * l;
            total += totalForPresent;
            total += std::min({l * w, w * h, h * l});
        });

        std::cout << "Total: " << total << std::endl;
        assert(total == 1598415);
    }

    {
        aoc::NamedAutoTimer t("part 2");
        int total = 0;

        std::for_each(presents.begin(), presents.end(), [&](auto& present) {
            auto[l, w, h] = present;
            int totalForPresent = std::min({2 * (l + w), 2 * (w + h), 2 * (h + l)});
            total += totalForPresent;
            total += l * w * h;
        });

        std::cout << "Total: " << total << std::endl;
        assert(total == 3812909);
    }
    return 0;
}