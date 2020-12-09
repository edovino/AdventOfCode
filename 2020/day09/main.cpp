#include <aoc.h>
#include <execution>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
//const int PREAMBLE_SIZE = 5;
#define INPUT INPUT_SRC_DIR"/input.txt"
const int PREAMBLE_SIZE = 25;

int main() {
    std::vector<int> numbers = aoc::io::loadAsVector<int>(INPUT);
    int firstInvalid = 0;

    {
        aoc::NamedAutoTimer t("part1");

        auto isInPreamble = [&](int i) {
            for (int j = i - PREAMBLE_SIZE; j < i - 2; ++j) {
                if (std::any_of(begin(numbers) + j + 1, begin(numbers) + i, [&](int num) { return num + numbers[j] == numbers[i]; })) return true;
            }
            return false;
        };

        int i;
        for (i = PREAMBLE_SIZE; i < numbers.size() && isInPreamble(i); ++i);

        firstInvalid = numbers[i];
        std::cout << "First invalid=" << firstInvalid << std::endl;
        assert(firstInvalid == 167829540);
    }

    {
        aoc::NamedAutoTimer t("part2");

        for (auto rangeStart = std::begin(numbers); rangeStart != std::end(numbers) - 1; ++rangeStart) {
            for (auto rangeEnd = rangeStart + 1; rangeEnd != std::end(numbers); ++rangeEnd) {
                if (std::accumulate(rangeStart, rangeEnd, 0) == firstInvalid) {
                    auto[min, max] = std::minmax_element(rangeStart, rangeEnd);

                    // theoretically these are parallelizable - but it makes things slower?!
//                if (std::reduce(std::execution::par_unseq, begin(numbers) + i, begin(numbers) + j, 0) == firstInvalid) {
//                    auto[min, max] = std::minmax_element(std::execution::par, begin(numbers) + i, begin(numbers) + j);

                    int weakness = *min + *max;
                    std::cout << "Weakness=" << weakness << std::endl;

                    assert(*min == 6402865);
                    assert(*max == 21642765);
                    assert(weakness == 6402865 + 21642765);

                    goto part2_done;
                }
            }
        }
        part2_done:;
    }

    return 0;
}