#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

template<typename P>
void setLights(int x1, int y1, int x2, int y2, int lights[], P pred) {
    for (int x = x1; x <= x2; ++x) {
        for (int y = y1; y <= y2; ++y) {
            int index = x + y * 1000;
            lights[index] = pred(lights[index]);
        }
    }
}

void part1() {
    aoc::NamedAutoTimer t("part 1");

    std::regex re(R"((.*) (\d*),(\d*) through (\d*),(\d*))");

    int lights[1000 * 1000];
    std::fill(std::begin(lights), std::end(lights), 0);

    aoc::io::loadLinewise(INPUT, [&](const std::string& line) {
        std::smatch match;
        if (std::regex_match(line, match, re)) {
            int startX = std::stoi(match[2]);
            int startY = std::stoi(match[3]);
            int endX = std::stoi(match[4]);
            int endY = std::stoi(match[5]);

            if (match[1] == "turn on") {
                setLights(startX, startY, endX, endY, lights, [](char current) { return 1; });
            } else if (match[1] == "turn off") {
                setLights(startX, startY, endX, endY, lights, [](char current) { return 0; });
            } else if (match[1] == "toggle") {
                setLights(startX, startY, endX, endY, lights, [](char current) { return current == 1 ? 0 : 1; });
            }
        }
    });

    int total = std::count(std::begin(lights), std::end(lights), 1);
    std::cout << "Total on: " << total << std::endl;
    assert(total == 377891);
}

void part2() {
    aoc::NamedAutoTimer t("part 2");
    std::regex re(R"((.*) (\d*),(\d*) through (\d*),(\d*))");

    int lights[1000 * 1000];
    std::fill(std::begin(lights), std::end(lights), 0);

    aoc::io::loadLinewise(INPUT, [&](const std::string& line) {
        std::smatch match;
        if (std::regex_match(line, match, re)) {
            int startX = std::stoi(match[2]);
            int startY = std::stoi(match[3]);
            int endX = std::stoi(match[4]);
            int endY = std::stoi(match[5]);

            if (match[1] == "turn on") {
                setLights(startX, startY, endX, endY, lights, [](int current) { return current + 1; });
            } else if (match[1] == "turn off") {
                setLights(startX, startY, endX, endY, lights, [](int current) { return std::max(current - 1, 0); });
            } else if (match[1] == "toggle") {
                setLights(startX, startY, endX, endY, lights, [](int current) { return current + 2; });
            }
        }
    });

    long total = std::accumulate(std::begin(lights), std::end(lights), 0);
    std::cout << "Total brightness: " << total << std::endl;
    assert(total == 14110788);
}

int main() {
    part1();
    part2();
    return 0;
}