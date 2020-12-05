#include <aoc.h>
#include <cassert>

//#define INPUT INPUT_SRC_DIR"/input-test-part1.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part2.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

void part1() {
    aoc::NamedAutoTimer t("part 1");

    int containerMass = 0;
    int totalFuelRequired = 0;
    aoc::io::loadLinewiseStringStream(INPUT, [&](auto& s) {
        s >> containerMass;
        totalFuelRequired += containerMass / 3 - 2;
    });

    std::cout << "Fuel required: " << totalFuelRequired << std::endl;
    assert(totalFuelRequired == 3226407);
}

int getFuelRequiredForMass(int mass) {
    int totalFuel = 0;
    int fuelRequired = mass / 3 - 2;
    if (fuelRequired > 0) totalFuel += fuelRequired + getFuelRequiredForMass(fuelRequired);

    return totalFuel;
}

void part2() {
    aoc::NamedAutoTimer t("part 2");

    int containerMass = 0;
    int totalFuelRequired = 0;
    aoc::io::loadLinewiseStringStream(INPUT, [&](auto& s) {
        s >> containerMass;
        totalFuelRequired += getFuelRequiredForMass(containerMass);
    });

    std::cout << "Fuel required: " << totalFuelRequired << std::endl;
    assert(totalFuelRequired == 4836738);
}

int main() {
    part1(); // 3226407
    part2(); //

    return 0;
}