#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part1-2.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part1-3.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part1-4.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

std::pair<int, int> decodeBoardingpass(const std::string& code) {
    int rowLo = 0, rowHi = 127, seatLo = 0, seatHi = 7;
    for (const auto& c : code) {
        switch (c) {
            case 'F':
                rowHi = (rowHi - rowLo) / 2 + rowLo;
                break;
            case 'B':
                rowLo = (rowHi - rowLo) / 2 + rowLo;
                break;
            case 'L':
                seatHi = (seatHi - seatLo) / 2 + seatLo;
                break;
            case 'R':
                seatLo = (seatHi - seatLo) / 2 + seatLo;
                break;
        }

    }
    return {rowHi, seatHi};
}

int main() {
    int maxSeatId = 0;
    {
        aoc::NamedAutoTimer t("part1");

        aoc::io::loadLinewise(INPUT, [&](const auto& s) {
            auto[row, seat] = decodeBoardingpass(s);
            auto seatId = row * 8 + seat;
            if (seatId > maxSeatId) maxSeatId = seatId;
            // std::cout << s << " " << row << "," << seat << " " << seatId << std::endl;
        });
        std::cout << "max seat ID: " << maxSeatId << std::endl;
    }

    {
        aoc::NamedAutoTimer t("part2");

        std::vector<int> seats(maxSeatId + 1);
        const auto firstSeat = begin(seats);
        const auto lastSeat = end(seats);
        std::fill(firstSeat, lastSeat, 0);

        aoc::io::loadLinewise(INPUT, [&](const auto& s) {
            auto[row, seat] = decodeBoardingpass(s);
            auto seatId = row * 8 + seat;
            seats[seatId] = 1;
        });

        auto mySeat = firstSeat + 1;
        for (; mySeat != seats.end() - 1; ++mySeat) {
            //   seat not yet taken?          seats next to me *are* taken?
            if (!seats[mySeat - firstSeat] && seats[mySeat - firstSeat - 1] && seats[mySeat - firstSeat + 1]) break;
        }

        std::cout << "my seat ID: " << mySeat - firstSeat << std::endl;
    }

    return 0;
}

