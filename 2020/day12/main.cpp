#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

void part1() {
    aoc::NamedAutoTimer t("part1");

    Pos myPos(0, 0);
    Vec myHeading(1, 0);

    aoc::io::loadLinewise(INPUT, [&](const auto& s) {
        char instr = s[0];
//        int amount = std::stoi(s.substr(1), 1);
        int amount = std::stoi(s.substr(1));
        //@formatter:off
        switch (instr) { // NOLINT(hicpp-multiway-paths-covered)
            case 'N': myPos.y+=amount; break;
            case 'S': myPos.y-=amount; break;
            case 'E': myPos.x+=amount; break;
            case 'W': myPos.x-=amount; break;
            case 'F': myPos += myHeading*amount; break;
            case 'L': for (int i = 0; i < amount; i+=90) { myHeading = Vec(-myHeading.y, myHeading.x); } break;
            case 'R': for (int i = 0; i < amount; i+=90) { myHeading = Vec(myHeading.y, -myHeading.x); } break;
        }
        //@formatter:on
    });
    std::cout << "Final position=" << myPos << " Manhattan distance=" << myPos.manhattanDistance() << std::endl;
    assert(myPos.manhattanDistance() == 1007);
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    Pos myPos(0, 0);
    Pos waypoint(10, 1);

    aoc::io::loadLinewise(INPUT, [&](const auto& s) {
        char instr = s[0];
//        int amount = std::stoi(s.substr(1), 1);
        int amount = std::stoi(s.substr(1));
        //@formatter:off
        switch (instr) { // NOLINT(hicpp-multiway-paths-covered)
            case 'N': waypoint.y+=amount; break;
            case 'S': waypoint.y-=amount; break;
            case 'E': waypoint.x+=amount; break;
            case 'W': waypoint.x-=amount; break;
            case 'F': for (int i = 0; i<amount; ++i) myPos += waypoint; break;
            case 'L': for (int i = 0; i < amount; i+=90) { waypoint = Vec(-waypoint.y, waypoint.x); } break;
            case 'R': for (int i = 0; i < amount; i+=90) { waypoint = Vec(waypoint.y, -waypoint.x); } break;
        }
        //@formatter:on
    });
    std::cout << "Final position=" << myPos << " Manhattan distance=" << myPos.manhattanDistance() << std::endl;
    assert(myPos.manhattanDistance() == 41212);
}

int main() {
    part1();
    part2();

    return 0;
}

