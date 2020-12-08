#include <aoc.h>
#include "md5.h"

#define SECRET_KEY "yzbqklnj"

void part1() {
    aoc::NamedAutoTimer t("part 1");

    std::string hash;
    int i = 0;
    do {
        i++;
        hash = MD5(SECRET_KEY + std::to_string(i)).finalize().hexdigest();
//        if (i % 1000 == 0) std::cout << i << std::endl;
    } while (hash.find("00000") != 0);

    std::cout << "number:" << i << std::endl;
    assert(i == 282749);
}

void part2() {
    aoc::NamedAutoTimer t("part 2");

    std::string hash;
    int i = 0;
    do {
        i++;
        hash = MD5(SECRET_KEY + std::to_string(i)).finalize().hexdigest();
//        if (i % 100000 == 0) std::cout << i << std::endl;
    } while (hash.find("000000") != 0);
    std::cout << "number:" << i << std::endl;

    assert(i == 9962624);
}

int main() {
    part1();
    part2();
    return 0;
}