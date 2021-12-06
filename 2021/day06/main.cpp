#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

std::vector<long> loadFishes();

void part1() {
    aoc::NamedAutoTimer t("part1");

    std::vector<long> fishesPerAge = loadFishes();
    for (int day = 0; day < 80; ++day) {
        std::rotate(begin(fishesPerAge), begin(fishesPerAge) + 1, end(fishesPerAge));
        fishesPerAge[6] += fishesPerAge[8];
    }
    long total = std::accumulate(begin(fishesPerAge), end(fishesPerAge), 0L);

    std::cout << "Total anglerFishes: " << total << std::endl;
    assert(total == 350917);
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    std::vector<long> fishesPerAge = loadFishes();
    for (int day = 0; day < 256; ++day) {
        std::rotate(begin(fishesPerAge), begin(fishesPerAge) + 1, end(fishesPerAge));
        fishesPerAge[6] += fishesPerAge[8];
    }

    long total = std::accumulate(begin(fishesPerAge), end(fishesPerAge), 0L);

    std::cout << "Total anglerFishes: " << total << std::endl;
    assert(total == 1592918715629);
}

int main() {
    part1();
    part2();

    return 0;
}

std::vector<long> loadFishes() {
    std::vector<long> fishesPerAge{0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::ifstream input(INPUT);
    int fishAge;
    char comma;
    while (input >> fishAge) {
        fishesPerAge[fishAge]++;
        input >> comma;
    }
    return fishesPerAge;
}
