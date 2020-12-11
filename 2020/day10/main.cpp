#include <aoc.h>
#include "numeric_ranges.hpp"

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part1-2.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

void part1() {
    aoc::NamedAutoTimer t("part1");

    long diff1;
    long diff3;

    std::vector<int> adapters = aoc::io::loadAsVector<int>(INPUT);
    adapters.push_back(0); // add charging outlet
    adapters.push_back(std::ranges::max(adapters) + 3); // add built-in adapter
    std::ranges::sort(adapters);

    std::vector<int> diff(adapters.size());
    tcb::adjacent_difference(adapters, begin(diff)); // std::ranges::adjacent_difference didn't make it into C++20, use shim (until C++23...)
//    std::adjacent_difference(begin(adapters), end(adapters), begin(diff)); // w/o ranges. not awful.

    diff1 = std::ranges::count(diff, 1);
    diff3 = std::ranges::count(diff, 3);

/*
    int currentRating = 0;
    int diff[] = {0, 0, 0, 0}; // we only care about 1 & 3 - no 2 exists, 0 is not possible,
    // but declaring this array this makes the code simpler

    for (const auto& rating : adapters) {
        diff[rating - currentRating]++;
        currentRating = rating;
    }
    diff1 = diff[1];
    diff3 = diff[3];
*/

    std::cout << "1-jolt diff=" << diff1 << std::endl;
    std::cout << "3-jolt diff=" << diff3 << std::endl;
    std::cout << "multiplied: " << diff1 * diff3 << std::endl;

    assert(diff1 == 71);
    assert(diff3 == 29);
}

void listNextPossible(const std::vector<int>& adapters, int max, int currentRating, long& count) {
//    if (count == 10000000) return; // goddammit - not waiting 6yrs
    if (currentRating == max) {
        count++;
        std::cout << count << std::endl;
        return;
    }

    for (const auto& item : adapters) {
        if (item - currentRating <= 3 && item > currentRating) {
            listNextPossible(adapters, max, item, count);
        }
    }
}

/*
 * not really interested in the full sequences - just the total amount of them
 *
 */
long countSteps(int i, std::vector<long>& alreadyCounted, const std::vector<int>& adapters) {
    if (i == adapters.size() - 1) return 1;
    if (alreadyCounted[i] > 0) return alreadyCounted[i]; // memoization https://en.wikipedia.org/wiki/Memoization

    long steps = 0;
    for (int j = i + 1; j < adapters.size(); ++j) {
        if (adapters[j] - adapters[i] <= 3) steps += countSteps(j, alreadyCounted, adapters);
    }

    alreadyCounted[i] = steps;

    return steps;
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    std::vector<int> adapters = aoc::io::loadAsVector<int>(INPUT);
    adapters.push_back(0); // add charging outlet
    adapters.push_back(std::ranges::max(adapters) + 3); // add built-in adapter
    std::ranges::sort(adapters);

/*
    // naive implementation: this takes approximately forever and a day
    long combinations = 0;
    int max = std::ranges::max(adapters);
    int currentRating = 0;
    listNextPossible(adapters, max, 0, combinations);
*/

    std::vector<long> alreadyCounted(adapters.size());
    // recursive fn w/ memoization
//    long combinations = countSteps(0, alreadyCounted, adapters);

/*
    // w00t! recursive lambda!
    std::function<long(int)> countSteps;
    countSteps = [&](int i) -> long {
        if (i == adapters.size() - 1) return 1;
        if (alreadyCounted[i] > 0) return alreadyCounted[i]; // memoization https://en.wikipedia.org/wiki/Memoization

        long steps = 0;
        for (int j = i + 1; j < adapters.size(); ++j) {
            if (adapters[j] - adapters[i] <= 3) steps += countSteps(j);
        }

        alreadyCounted[i] = steps;

        return steps;
    };
*/
    // extra w00t! recursive lambda, with auto!
    // needs weird trick - feed lambda a ref to self: https://stackoverflow.com/a/40873505/306802,
    // http://pedromelendez.com/blog/2015/07/16/recursive-lambdas-in-c14/
    //
    // well, that's just... well. possibly faster than std::function variety...
    const auto countSteps = [&](int i) {
        auto countSteps_impl = [&](int i, auto& countSteps_ref) {
            if (i == adapters.size() - 1) return 1L; // force correct type deduction
            if (alreadyCounted[i] > 0) return alreadyCounted[i]; // memoization https://en.wikipedia.org/wiki/Memoization
            long steps = 0;
            for (int j = i + 1; j < adapters.size(); ++j) {
                if (adapters[j] - adapters[i] <= 3) steps += countSteps_ref(j, countSteps_ref);
            }
            alreadyCounted[i] = steps;
            return steps;
        };
        return countSteps_impl(i, countSteps_impl);
    };
    long combinations = countSteps(0);

//  Wow...
/*
    std::map<long, long> counts{{0, 1}};
    for (auto adapter : adapters) counts[adapter] += counts[adapter - 1] + counts[adapter - 2] + counts[adapter - 3];
    long combinations = counts[adapters.back()]; // BAM!
*/

    std::cout << "Possible combinations: " << combinations << std::endl;
    assert(combinations == 86812553324672);
}

int main() {
    part1();
    part2();

    return 0;
}

