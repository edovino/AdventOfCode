#include <aoc.h>
//#include "folly/container/F14Map.h"
//#include "absl/container/flat_hash_map.h" - should be faster, but I notice nothing!?

void part1() {
    aoc::NamedAutoTimer t("part1");

    std::unordered_map<int, int> lastSeen;
    int seq[] = {2, 0, 1, 9, 5};
    std::ranges::for_each(seq, [&](const auto& i) { lastSeen[i] = lastSeen.size() + 1; });// mogrify

    int previous = 19;
    for (int turn = lastSeen.size() + 2; turn <= 2020; ++turn) {
        int next = 0;
        if (lastSeen.contains(previous)) next = turn - lastSeen[previous] - 1;
        lastSeen[previous] = turn - 1;
        previous = next;
    }
    std::cout << " Final number: " << previous << std::endl;

    assert(previous == 1009);
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    std::unordered_map<int, int> lastSeen(6000000);

    std::vector seq = {2, 0, 1, 9, 5};
    std::ranges::for_each(seq, [&](const auto& i) { lastSeen[i] = lastSeen.size() + 1; });// mogrify

    int previous = 19;
    for (int turn = seq.size() + 2; turn <= 30000000; ++turn) {
        int next = 0;
        if (lastSeen.contains(previous)) next = turn - lastSeen[previous] - 1;
        lastSeen[previous] = turn - 1;
        previous = next;
    }
    std::cout << " Final: " << previous << std::endl;

    assert(previous == 62714);
}

int main() {
    part1();
    part2();

    return 0;
}

