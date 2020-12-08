#include <iostream>
#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

void part1() {
    aoc::NamedAutoTimer t("part1");

    int currentFloor = 0;

    aoc::io::loadCharwise(INPUT, [&](char& c) {
        if (c == '(') ++currentFloor;
        if (c == ')') --currentFloor;
    });

    std::cout << "Floor: " << currentFloor << std::endl;
    assert(currentFloor == 138);
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    int currentFloor = 0;
    int position = 0;
    bool found = false;

    aoc::io::loadCharwise(INPUT, [&](char& c) {
        position++;
        if (c == '(') ++currentFloor;
        if (c == ')') --currentFloor;

        if (currentFloor == -1 && !found) {
            found = true;
            std::cout << "Position: " << position << std::endl;
            assert(position == 1771);
        }
    });
}

int main() {
    part1();
    part2();

    return 0;
}