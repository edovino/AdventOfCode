#include <aoc.h>

// #INPUT_SRC_DIR is a #define set by CMake
//#define INPUT INPUT_SRC_DIR"/input-test-part1-1.txt"
#define INPUT INPUT_SRC_DIR"/input.txt"

int smashIntoTrees(const std::set<Pos>& trees, int width, int height, const Vec& slope) {
    int smashedTrees = 0;

    Pos me(0, 0);
    while (me.y <= height) {
        if (trees.contains(me)) smashedTrees++;
        me.x = (me.x + slope.x) % width;
        me.y += slope.y;
    }

    return smashedTrees;
}

std::tuple<std::set<Pos>, int, int> loadMap() {
    std::set<Pos> trees;
    int width = 0;
    int height = 0;

    aoc::io::loadLinewise(INPUT, [&](auto s) {
        if (s.length() > width) width = s.length();
        for (int i = 0; i < width; ++i) if (s[i] == '#') trees.insert(Pos(i, height));
        ++height;
    });
    --height;

    return std::tuple(trees, width, height);
}

int main() {
    auto[trees, width, height] = loadMap();

    {
        aoc::NamedAutoTimer t("part1");

        int treeCount = smashIntoTrees(trees, width, height, {3, 1});
        std::cout << treeCount << std::endl; // 162
    }

    {
        aoc::NamedAutoTimer t("part2");

        Vec slopes[] = {{1, 1},
                        {3, 1},
                        {5, 1},
                        {7, 1},
                        {1, 2}};

        std::vector<int> treeCounts; // { 80, 162, 77, 83, 37 }
        for (const auto& slope : slopes) {
            int smashedTrees = smashIntoTrees(trees, width, height, slope);
            treeCounts.push_back(smashedTrees);
//            std::cout << slope << " : " << smashedTrees << std::endl;
        }

        std::cout << "product: " << std::accumulate(begin(treeCounts), end(treeCounts), 1L, std::multiplies()) << std::endl; // 3064612320
    }

    return 0;
}