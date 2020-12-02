#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

void part1() {
    aoc::NamedAutoTimer t("part1");

    auto ints = aoc::io::loadAsVector<int>(INPUT);

// brute force - sorting required as opt
//    std::sort(begin(ints), end(ints));
//    for (int i = 0; i < ints.size(); ++i) {
//        for (int j = i + 1; j < ints.size(); ++j) {
//            if (ints[i] + ints[j] > 2020) break;
//            if (ints[i] + ints[j] != 2020) continue;
//            std::cout << ints[i] << "*" << ints[j] << " = " << ints[i] * ints[j] << std::endl;
//            return;
//        }
//    }

    // slightly less brute force - sorting not necessary?
    for (const auto& firstInt : ints) {
        auto secondInt = std::find_if(begin(ints), end(ints), [&](int i) { return firstInt + i == 2020; });
        if (secondInt == end(ints)) continue;
        std::cout << firstInt << "*" << *secondInt << " = " << firstInt * *secondInt << std::endl;
        return;
    }
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    auto ints = aoc::io::loadAsVector<int>(INPUT);

    std::sort(begin(ints), end(ints));

// brute force
//    for (int i = 0; i < ints.size(); ++i) {
//        for (int j = i + 1; j < ints.size(); ++j) {
//            if (ints[i] + ints[j] > 2020) break;
//            for (int k = j + 1; k < ints.size(); ++k) {
//                if (k == j || k == i) continue;
//                if (ints[i] + ints[j] + ints[k] > 2020) break;
//                if (ints[i] + ints[j] + ints[k] != 2020) continue;
//                std::cout << ints[i] << "*" << ints[j] << "*" << ints[k] << " = " << ints[i] * ints[j] * ints[k] << std::endl;
//                return;
//            }
//        }
//    }

    // slightly less brute force
    for (const auto& firstInt : ints) {
        for (const auto& secondInt : ints) {
            if (firstInt == secondInt) continue;
            if (firstInt + secondInt > 2020) break;
            auto thirdInt = std::find_if(begin(ints), end(ints), [&](int i) { return firstInt + secondInt + i == 2020; });
            if (thirdInt == end(ints)) continue;
            std::cout << firstInt << "*" << secondInt << "*" << *thirdInt << " = " << firstInt * secondInt * *thirdInt << std::endl;
            return;
        }
    }
}

int main() {
    part1(); // 376*1644=618144
    part2(); // 289*480*1251=173538720

    return 0;
}