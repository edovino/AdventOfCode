#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

void part1() {
    aoc::NamedAutoTimer t("part1");

    std::vector<std::string> current, next;
    current = aoc::io::loadAsVector<std::string>(INPUT);

    const int width = current[0].size();
    const int height = current.size();

    auto isOccupied = [&](int x, int y) {
        if (y < 0 || x < 0 || y == height || x == width) return false;
        return current[y][x] == '#';
    };

    auto countOccupied = [&](int x, int y) {
        int occupied = 0;

        for (int offsetX = -1; offsetX < 2; ++offsetX) {
            for (int offsetY = -1; offsetY < 2; ++offsetY) {
                if (offsetX == 0 && offsetY == 0) continue;
                if (isOccupied(x + offsetX, y + offsetY)) occupied++;
            }
        }
        return occupied;
    };

    do {
        next = current;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (current[y][x] == '.') continue;
                int occupied = countOccupied(x, y);
                if (current[y][x] == 'L' && occupied == 0) next[y][x] = '#';
                if (current[y][x] == '#' && occupied >= 4) next[y][x] = 'L';
            }
        }
        std::swap(current, next);
    } while (current != next);

    int totalOccupied = 0;
    for (const auto& row : current) totalOccupied += std::count(begin(row), end(row), '#');
    std::cout << "Total occupied seats=" << totalOccupied << std::endl;

    assert(totalOccupied == 2263);
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    std::vector<std::string> current, next;
    current = aoc::io::loadAsVector<std::string>(INPUT);

    const int width = current[0].size();
    const int height = current.size();

    auto seesOccupied = [&](int x, int y, int offsetX, int offsetY) {
        int testX = x + offsetX;
        int testY = y + offsetY;

        while (testY >= 0 && testX >= 0 && testY < height && testX < width && current[testY][testX] != 'L') {
            if (current[testY][testX] == '#') return true;
            testX += offsetX;
            testY += offsetY;
        }

        return false;
    };

    auto countOccupied = [&](int x, int y) {
        int occupied = 0;

        for (int offsetX = -1; offsetX < 2; ++offsetX) {
            for (int offsetY = -1; offsetY < 2; ++offsetY) {
                if (offsetX == 0 && offsetY == 0) continue;
                if (seesOccupied(x, y, offsetX, offsetY)) occupied++;
            }
        }
        return occupied;
    };


    do {
        next = current;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (current[y][x] == '.') continue;
                int occupied = countOccupied(x, y);
                if (current[y][x] == 'L' && occupied == 0) next[y][x] = '#';
                if (current[y][x] == '#' && occupied >= 5) next[y][x] = 'L';
            }
        }

        std::swap(current, next);
    } while (current != next);

    int totalOccupied = 0;
    for (const auto& row : current) totalOccupied += std::count(begin(row), end(row), '#');
    std::cout << "Total occupied seats=" << totalOccupied << std::endl;

    assert(totalOccupied == 2002);
}

int main() {
    part1();
    part2();

    return 0;
}

