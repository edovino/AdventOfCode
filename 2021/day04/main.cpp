#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

class BingoBoard {
    public:
        bool bingo = false;
        std::vector<int> numbers;

        void load(std::ifstream& input) {
            int num;
            for (int i = 0; i < 25; ++i) {
                input >> num;
                numbers.emplace_back(num);
            }
        }

        bool tryNumber(int num) {
            for (int& number: numbers) {
                if (number == num) {
                    number = -1;
                    bingo = checkBingo();
                }
            }
            return bingo;
        }

        int sumRow(int idx) {
            int total = 0;
            for (int row = 0; row < 5; ++row) {
                if (numbers[row + 5 * idx] != -1) total += numbers[row + 5 * idx];
            }

            return total;
        }

        int sumCol(int idx) {
            int total = 0;
            for (int col = 0; col < 5; ++col) {
                if (numbers[col * 5 + idx] != -1) total += numbers[col * 5 + idx];
            }

            return total;
        }

        int sumRemaining() {
            int total = 0;
            for (const auto& number: numbers) total += (number != -1) ? number : 0;
            return total;
        }

        bool checkBingo() {
            for (int i = 0; i < 5; ++i) if (sumCol(i) == 0 || sumRow(i) == 0) return true;
            return false;
        }
};

int main() {
    aoc::NamedAutoTimer t("all");

    std::ifstream input(INPUT);
    input >> std::noskipws;

    std::vector<int> calledNumbers;
    int num;
    char separator;

    while (input >> num) {
        calledNumbers.emplace_back(num);
        input >> separator;
        if (separator != ',') break;
    }

    input >> std::skipws;

    std::vector<BingoBoard> boards;
    do {
        BingoBoard board;
        board.load(input);
        boards.emplace_back(board);
    } while (!input.eof());

    std::cout << "Loaded " << boards.size() << " bingo boards" << std::endl;

    int firstBoard = -1;
    int lastBoard = -1;
    int calledNumber = 0;

    // start calling the numbers
    for (const auto& number: calledNumbers) {
        for (int boardIdx = 0; boardIdx < boards.size(); ++boardIdx) {
            if (boards[boardIdx].bingo) continue;
            if (boards[boardIdx].tryNumber(number)) {
                if (firstBoard == -1) {
                    std::cout << "First Bingo! on board " << boardIdx << std::endl;
                    firstBoard = boardIdx;

                    assert(boardIdx == 49);
                    assert(boards[boardIdx].sumRemaining() == 871);
                    assert(boards[boardIdx].sumRemaining() * number == 35711);
                    t.lap("part 1");
                }
                lastBoard = boardIdx;
                calledNumber = number;
            }
        }
    }

    assert(lastBoard == 30);
    assert(boards[lastBoard].sumRemaining() == 266);
    assert(boards[lastBoard].sumRemaining() * calledNumber == 5586);
    t.lap("part 2");

    return 0;
}

