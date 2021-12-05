#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part1-2.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part1-3.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part2-1.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part2-2.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part2-3.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

void part1() {
    aoc::NamedAutoTimer t("part1");

    std::map<aoc::Pos, int> positions;

    aoc::io::eachLineStringStream(INPUT, [&positions](auto& sstr) {
        int startX, startY, endX, endY;
        char comma;
        std::string dummy;
        sstr >> startX >> comma >> startY >> dummy >> endX >> comma >> endY;

        if (startX != endX && startY != endY) return;

        aoc::Vec step(aoc::sgn(endX - startX), aoc::sgn(endY - startY));
        aoc::Pos pos(startX, startY);
        aoc::Pos endPos(endX, endY);

        auto updatePos = [&](const auto& pos) {
            if (positions[pos]) {
                positions[pos]++;
            } else {
                positions[pos] = 1;
            }
        };

        while (pos != endPos) {
            updatePos(pos);
            pos += step;
        }
        updatePos(pos); // handle end position
    });

    auto count = std::ranges::count_if(positions, [](const auto& kvpair) {
        auto[key, value] = kvpair;
        return value >= 2;
    });

    std::cout << "Count=" << count << std::endl;
    assert(count == 5690);
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    std::map<aoc::Pos, int> positions;

    aoc::io::eachLineStringStream(INPUT, [&positions](auto& sstr) {
        int startX, startY, endX, endY;
        char comma;
        std::string dummy;
        sstr >> startX >> comma >> startY >> dummy >> endX >> comma >> endY;

        aoc::Vec step(aoc::sgn(endX - startX), aoc::sgn(endY - startY));
        aoc::Pos pos(startX, startY);
        aoc::Pos endPos(endX, endY);

        auto updatePos = [&](const auto& pos) {
            if (positions[pos]) {
                positions[pos]++;
            } else {
                positions[pos] = 1;
            }
        };

        while (pos != endPos) {
            updatePos(pos);
            pos += step;
        }
        updatePos(pos); // handle end position
    });

    auto count = std::ranges::count_if(positions, [](const auto& kvpair) {
        auto[key, value] = kvpair;
        return value >= 2;
    });

    std::cout << "Count=" << count << std::endl;
    assert(count == 17741);
}

int main() {
    part1();
    part2();

    return 0;
}

