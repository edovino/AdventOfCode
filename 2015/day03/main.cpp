#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

void part1() {
    aoc::NamedAutoTimer t("part 1");
    int santaX = 0;
    int santaY = 0;
    std::set<std::pair<int, int>> uniqueHouses;

    aoc::io::loadCharwise(INPUT, [&](char& c) {
        if (c == '^') {
            santaY--;
        } else if (c == 'v') {
            santaY++;
        } else if (c == '>') {
            santaX++;
        } else { // (c=='<')
            santaX--;
        }
        uniqueHouses.insert({santaX, santaY});
    });

    std::cout << "Total unique houses: " << uniqueHouses.size() << std::endl;
    assert(uniqueHouses.size() == 2572);
}

void part2() {
    aoc::NamedAutoTimer t("part 2");

    int santaX[]{0, 0};
    int santaY[]{0, 0};
    int santaIndex = 0;

    std::set<std::pair<int, int>> uniqueHouses;

    aoc::io::loadCharwise(INPUT, [&](char& c) {
        if (c == '^') {
            santaY[santaIndex]--;
        } else if (c == 'v') {
            santaY[santaIndex]++;
        } else if (c == '>') {
            santaX[santaIndex]++;
        } else { // (c=='<')
            santaX[santaIndex]--;
        }
        uniqueHouses.insert({santaX[santaIndex], santaY[santaIndex]});
        santaIndex = (santaIndex + 1) % 2;
    });

    std::cout << "Total unique houses: " << uniqueHouses.size() << std::endl;
    assert(uniqueHouses.size() == 2631);
}

int main() {
    part1();
    part2();
    return 0;
}