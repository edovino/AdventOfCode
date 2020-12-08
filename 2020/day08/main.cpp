#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

struct Instruction {
    std::string op;
    int val;
    bool operator==(const std::string& rhs) const { return op == rhs; } // for use in std::find
};

struct Handheld {
    int pc = 0; // Z80a nostalgia
    int a = 0;

    bool terminated = false;

    std::set<int> visited;
    std::vector<Instruction> program;

    //@formatter:off
    std::map<const std::string, std::function<void()>> instructions{
            {"acc", [&]() { a += program[pc].val; ++pc; }},
            {"jmp", [&]() { pc += program[pc].val; }},
            {"nop", [&]() { ++pc; }}
    };
    //@formatter:on

    void loadProgram(const std::string& filename) {
        reset();
        aoc::io::loadLinewise(filename, [&](const auto& line) {
            program.emplace_back(line.substr(0, 3), std::stoi(line.substr(3)));
        });
    }

    void exec() {
        if ((terminated = pc >= program.size())) return;

        visited.insert(pc);
        instructions[program[pc].op]();
    }

    [[nodiscard]] bool isLooping() const {
        return visited.contains(pc);
    }

    void reset() {
        a = 0;
        pc = 0;
        visited.clear();
        terminated = false;
    }
};

void part1() {
    aoc::NamedAutoTimer t("part1");

    Handheld hh;
    hh.loadProgram(INPUT);

    while (!hh.isLooping()) hh.exec();

    std::cout << "Bootloop! acc=" << hh.a << std::endl;
    assert(hh.a == 1487);
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    Handheld hh;
    hh.loadProgram(INPUT);

    int patchLocation = 0;
    while (!hh.terminated) {
        hh.reset();
        while (!hh.isLooping() && !hh.terminated) hh.exec();

        hh.program[patchLocation].op = "jmp"; // unpatch
        // patch next jmp
        patchLocation = std::find(begin(hh.program) + patchLocation + 1, end(hh.program), "jmp") - begin(hh.program);
        hh.program[patchLocation].op = "nop";
    }

    std::cout << (hh.terminated ? "Terminated!" : "Bootloop...") << " acc=" << hh.a << std::endl;
    assert(hh.a == 1607);
}

int main() {
    part1();
    part2();

    return 0;
}

