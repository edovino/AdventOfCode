#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part2-1.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part2-2.txt"
//#define INPUT INPUT_SRC_DIR"/input-test-part2-3.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

std::pair<int, std::string> loadInput(const std::string& filename) {
    std::fstream input;
    input.open(INPUT);

    long myDeparture;
    input >> myDeparture;
    std::string scheduleString;
    input >> scheduleString;
    input.close();

    return {myDeparture, scheduleString};
}


void part1() {
    aoc::NamedAutoTimer t("part1");

    auto[myDeparture, scheduleString] = loadInput(INPUT);

    int minWaitBus = 0;
    int minWaitTime = INT32_MAX;

    std::istringstream iss(scheduleString);
    while (iss) {
        std::string busString;
        if (!std::getline(iss, busString, ',')) break;
        if (busString == "x") continue; // non-existent schedule entry
        int bus = std::stoi(busString);

        int div = myDeparture / bus;
        int nextPassPostMyDeparture = bus * (div + 1);
        int waitTime = nextPassPostMyDeparture - myDeparture;
        if (waitTime < minWaitTime) {
            minWaitTime = waitTime;
            minWaitBus = bus;
        }
    }

    std::cout << "Bus: " << minWaitBus << " " << minWaitTime << "minute wait, product: " << minWaitBus * minWaitTime << std::endl;

    assert(minWaitBus * minWaitTime == 2045);
}

void part2() {
    aoc::NamedAutoTimer t("part2");

    auto[myDeparture, scheduleString] = loadInput(INPUT);


    auto tokens = aoc::tokenizr(scheduleString, ',');
    std::vector<int> buses;
    std::ranges::transform(tokens, std::back_inserter(buses), [](const auto& bus) { return bus == "x" ? 0 : std::stoi(bus); });

    //is this https://en.wikipedia.org/wiki/Chinese_remainder_theorem#Search_by_sieving ? or other impl of LCM?
    long time = 0;
    long timeIncrement = buses[0];
    for (int i = 1; i < buses.size(); ++i) {
        if (buses[i] == 0) continue; // non-existent schedule entry
        while ((time + i) % buses[i] != 0) time += timeIncrement;
        timeIncrement *= buses[i];
    }

    /*
     * Chinese Remainder Theorem
     */
    /*
    int minute = -1;
    uint64_t mult = 0;
    for (const auto& bus_ID : bus_IDs_) {
        minute++;
        if (bus_ID == 0) continue;
        if (minute == 0) {
            mult = (uint64_t) bus_ID;
        } else {
            //std::cout << bus_ID << ": " << bus_ID - (minute % bus_ID) << "\n";
            wait_time_[bus_ID] = bus_ID - (minute % bus_ID);
        }
    }
    uint64_t timestamp = 0;

    for (auto it = wait_time_.begin(); it != wait_time_.end(); it++) {
        //std::cout << (*it).first << " " << (*it).second << " \n";
        while ((timestamp % (*it).first) != (*it).second) {
            timestamp += mult;
        }
        mult *= (*it).first;
        //std::cout << timestamp << "\n";
    }
    */

    std::cout << "Timestamp=" << time << std::endl;

    assert(time == 402251700208309);
}

int main() {
    part1();
    part2();

    return 0;
}

