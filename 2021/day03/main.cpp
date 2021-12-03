#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

void part1() {
    aoc::NamedAutoTimer t("part1");

    int totalStrings = 0;
    std::vector<int> bitcounts{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    aoc::io::eachLine(INPUT, [&](const std::string& s) {
        totalStrings++;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '1') bitcounts[i]++;
        }
    });

    std::string bitstring;
    for (int bitcount: bitcounts) bitstring += (bitcount > totalStrings / 2 ? '1' : '0');

    int gammaRate = std::stoi(bitstring, nullptr, 2);
    std::cout << "gamma rate: " << bitstring << " = " << gammaRate << std::endl;

    for (char& bit: bitstring) bit = (bit == '0') ? '1' : '0';

    int epsilonRate = std::stoi(bitstring, nullptr, 2);
    std::cout << "epsilon rate: " << bitstring << " = " << epsilonRate << std::endl;

    int powerConsumption = gammaRate * epsilonRate;
    std::cout << "power consumption:" << powerConsumption << std::endl;

    assert(gammaRate == 2849);
    assert(epsilonRate == 1246);
    assert(powerConsumption == 3549854);
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    auto lines = aoc::io::eachLineToVector(INPUT);

    auto filteredLinesOxygen = lines;
    auto filteredLinesCO2 = lines;

    for (int bit = 0; bit < lines[0].length(); ++bit) {
        if (filteredLinesOxygen.size() > 1) {
            auto oneCount = std::ranges::count_if(filteredLinesOxygen, [&](auto& line) { return line[bit] == '1'; });
            auto zeroCount = std::ranges::count_if(filteredLinesOxygen, [&](auto& line) { return line[bit] == '0'; });

//            auto shouldKeep = [&](auto& line) { return line[bit] == ((oneCount > zeroCount || oneCount == zeroCount) ? '1' : '0'); };
//            std::vector<std::string> tmpFiltered;
//            std::ranges::copy_if(filteredLinesOxygen, std::back_inserter(tmpFiltered), shouldKeep);
//            filteredLinesOxygen = tmpFiltered;

            auto shouldRemove = [&](auto& line) { return line[bit] == ((oneCount > zeroCount || oneCount == zeroCount) ? '0' : '1'); };
            auto[begin, end] = std::ranges::remove_if(filteredLinesOxygen, shouldRemove);
            filteredLinesOxygen.erase(begin, end);
        }

        if (filteredLinesCO2.size() > 1) {
            auto oneCount = std::ranges::count_if(filteredLinesCO2, [&](auto& line) { return line[bit] == '1'; });
            auto zeroCount = std::ranges::count_if(filteredLinesCO2, [&](auto& line) { return line[bit] == '0'; });

//            std::vector<std::string> tmpFiltered;
//            auto shouldKeep = [&](auto& line) { return line[bit] == ((oneCount > zeroCount || oneCount == zeroCount) ? '0' : '1'); };
//            std::ranges::copy_if(filteredLinesCO2, std::back_inserter(tmpFiltered), shouldKeep);
//            filteredLinesCO2 = tmpFiltered;

            auto shouldRemove = [&](auto& line) { return line[bit] == ((oneCount > zeroCount || oneCount == zeroCount) ? '1' : '0'); };
            auto[begin, end] = std::ranges::remove_if(filteredLinesCO2, shouldRemove);
            filteredLinesCO2.erase(begin, end);
        }
    }

    long oxygenGeneratorRating = std::stol(filteredLinesOxygen[0], nullptr, 2);
    long co2ScrubberRating = std::stol(filteredLinesCO2[0], nullptr, 2);

    std::cout << "oxygenGeneratorRating: " << filteredLinesOxygen[0] << " = " << oxygenGeneratorRating << std::endl;
    std::cout << "co2ScrubberRating: " << filteredLinesCO2[0] << " = " << co2ScrubberRating << std::endl;

    long lifeSupportRating = oxygenGeneratorRating * co2ScrubberRating;
    std::cout << "lifeSupportRating:" << lifeSupportRating << std::endl;

    assert(oxygenGeneratorRating == 2783);
    assert(co2ScrubberRating == 1353);
    assert(lifeSupportRating == 3765399);
}

int main() {
    part1();
    part2();

    return 0;
}

