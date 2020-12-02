#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

template<typename F>
int countValidPasswords(F validator) {
    std::ifstream in(INPUT);
    int min, max;
    char letter, dummy;
    std::string password;

    int valid = 0;

    while (true) {
        in >> min;
        if (in.eof()) break;
        in >> max;
        max = -max;
        in >> letter;
        in >> dummy;
        in >> password;

        validator(min, max, letter, password, valid);
    }
    return valid;
}

void part1() {
    aoc::NamedAutoTimer t("part1");

    int valid = countValidPasswords([](int min, int max, char letter, std::string& password, int& valid) {
        int count = std::count(begin(password), end(password), letter);
        if (count >= min && count <= max) valid++;
    });

    std::cout << "Valid: " << valid << std::endl;
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    int valid = countValidPasswords([](int firstPos, int secondPos, char letter, std::string& password, int& valid) {
        if ((password[firstPos - 1] == letter) ^ (password[secondPos - 1] == letter)) valid++;
    });

    std::cout << "Valid: " << valid << std::endl;
}

int main() {
    part1(); // 614
    part2(); // 354

    return 0;
}

