#pragma once

#include <string>
#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#include <tuple>
#include <thread>
#include <regex>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
#include <cassert>


namespace aoc {
    template<typename T>
    int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }

    void sleepMS(int ms);
    void waitForKeypress(int intervalMS = 100);
    int _kbhit();
    bool isNumber(std::string s);

    /**
     * Checks if the value is within the range lower-higher, *excluding* the boundaries
     * @tparam T type
     * @tparam Compare comparator predicate to use
     * @param val the value to check
     * @param lo lower bound *exclusive*
     * @param hi higher bound *exclusive*
     * @param comp comparator predicate
     * @return true if the value is between lo and hi (exclusive)
     */

    template<class T, class Compare>
    bool between(T const& val, T const& lower, T const& higher, Compare comp) {
        return comp(lower, val) && comp(val, higher);
    }

    template<class T>
    bool between(T const& val, T const& lo, T const& hi) {
        return between(val, lo, hi, std::less<T>());
    }

    /**
     * Checks if the value is with the range lo-hi, *including* the boundaries
     * @tparam T
     * @tparam Compare
     * @param val
     * @param lo
     * @param hi
     * @param comp
     * @return
     */
    template<class T, class Compare>
    bool in_range(T const& val, T const& lo, T const& hi, Compare comp) {
        return comp(lo - 1, val) && comp(val, hi + 1);
    }

    template<class T>
    bool in_range(T const& val, T const& lo, T const& hi) {
        return in_range(val, lo, hi, std::less<T>());
    }

    class NamedAutoTimer {
        public:
            NamedAutoTimer(std::string name) : name{name} {
                timerStart = std::chrono::steady_clock::now();
                std::cout << "=== Started " << name << std::endl;
            }

            ~NamedAutoTimer() {
                auto timerEnd = std::chrono::steady_clock::now();
                std::cout << "=== Finished " << name << ", took ";
                printFormattedDuration(timerEnd);
                std::cout << std::endl;
            }

            void lap() {
                auto timerLap = std::chrono::steady_clock::now();
                std::cout << "=== Lap for " << name << ": ";
                printFormattedDuration(timerLap);
                std::cout << std::endl;
            }

        private:
            std::string name;
            std::chrono::steady_clock::time_point timerStart;

            void printFormattedDuration(std::chrono::steady_clock::time_point timerEnd) {
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timerEnd - timerStart).count();
                if (duration > 1000) {
                    duration = std::chrono::duration_cast<std::chrono::milliseconds>(timerEnd - timerStart).count();
                    std::cout << duration << "ms";
                } else {
                    std::cout << duration << "us";
                }
            }
    };
}

template<typename T>
struct Vec_T {
    Vec_T(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    T x, y, z;

    Vec_T sgn(const Vec_T& rhs) {
        return Vec_T(aoc::sgn(rhs.x - this->x),
                     aoc::sgn(rhs.y - this->y),
                     aoc::sgn(rhs.z - this->z));
    }

    T manhattanDistance() const { // manhattan distance relative to origin
        return std::abs(x) + std::abs(y) + std::abs(z);
    }

    void reduce() { // not normalize as in 'create unity vector', but reduce by GCD
        int _gcd = std::gcd(x, y);
        x /= _gcd;
        y /= _gcd;
        //FIXME: z
    }

    Vec_T reduced() {
        int _gcd = std::gcd(x, y);
        T newX = x / _gcd;
        T newY = y / _gcd;
        //FIXME: z
        return Vec_T(newX, newY);
    }

    T dotProduct(const Vec_T& rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    T determinant(const Vec_T& rhs) const {
        return x * rhs.y - y * rhs.x;
    }

    Vec_T crossProduct(const Vec_T& rhs) {
        return Vec_T((y * rhs.z) - (z * rhs.y),
                     (z * rhs.x) - (x * rhs.z),
                     (x * rhs.y) - (y * rhs.x));
    }

    Vec_T operator+=(const Vec_T& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }

    Vec_T operator+(const Vec_T& rhs) const {
        return Vec_T(*this) += rhs;
    }

    Vec_T operator-=(const Vec_T& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        return *this;
    }

    Vec_T operator-(const Vec_T& rhs) const {
        return Vec_T(*this) -= rhs;
    }

    Vec_T operator/=(const int s) {
        this->x /= s;
        this->y /= s;
        this->z /= s;
        return *this;
    }

    Vec_T operator/(const int s) const {
        return Vec_T(*this) /= s;
    }

    Vec_T operator*=(const int s) {
        this->x *= s;
        this->y *= s;
        this->z *= s;
        return *this;
    }

    Vec_T operator*(const int s) const {
        return Vec_T(*this) *= s;
    }

    T length() const {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    void normalize() {
        this->x /= length();
        this->y /= length();
        this->z /= length();
    }

    Vec_T normalized() const {
        return Vec_T(*this) / length();
    }

    float angleTo(const Vec_T& other) const {
        float dot = this->dotProduct(other);
        float det = x * other.y - y * other.x;
        return float(std::atan2(det, dot));
    }

    bool operator==(const Vec_T& rhs) const {
        return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
    }

    bool operator!=(const Vec_T& rhs) const {
        return *this != rhs;
    }

    bool operator<(const Vec_T& rhs) const {
        if (x < rhs.x) return true;
        if (rhs.x < x) return false;
        if (y < rhs.y) return true;
        if (rhs.y < y) return false;
        return z < rhs.z;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec_T& Vec) {
        os << "<x=" << Vec.x << ", y=" << Vec.y << ", z=" << Vec.z << ">";
        return os;
    }
};

typedef Vec_T<int> Vec;
typedef Vec_T<int> Pos;

Vec headingForChar(char c);
char charForHeading(const Vec& heading);

struct Node {
    Node() {}
    Node(int x, int y) : pos(x, y), parent(nullptr) {}
    Node(const Pos& p) : pos(p), parent(nullptr) {}
    Pos pos;
    Node* parent;
    bool operator==(const Node& rhs) const {
        return pos == rhs.pos && parent == rhs.parent;
    }

    bool operator!=(const Node& rhs) const {
        return !(rhs == *this);
    }
    bool operator<(const Node& rhs) const {
        if (pos < rhs.pos)
            return true;
        if (rhs.pos < pos)
            return false;
        return parent < rhs.parent;
    }
    bool operator>(const Node& rhs) const {
        return rhs < *this;
    }
    bool operator<=(const Node& rhs) const {
        return !(rhs < *this);
    }
    bool operator>=(const Node& rhs) const {
        return !(*this < rhs);
    }
};

namespace aoc::io {
    template<typename T>
    void loadCharwise(const std::string& filename, T pred) {
        std::fstream input;
        input.open(filename);

        char c;
        while (input >> c) pred(c);

        input.close();
    }

    template<typename T>
    void loadLinewise(const std::string& filename, T pred) {
        std::fstream input;
        input.open(filename);

        std::string line;
        while (std::getline(input, line)) pred(line);

        input.close();
    }

    template<typename T>
    void loadLinewiseStringStream(std::istream& input, T pred) {
        std::string line;
        while (std::getline(input, line)) {
            std::istringstream stream(line);
            pred(stream);
        }
    }

    template<typename T>
    void loadLinewiseStringStream(const std::string& filename, T pred) {
        std::fstream input;
        input.open(filename);
        loadLinewiseStringStream(input, pred);

        input.close();
    }

    std::string loadIntoString(const std::string& filename);

    template<typename T>
    std::vector<T> loadAsVector(const std::string& file) {
        std::ifstream input;
        input.open(file);

        std::vector<T> data;
        T value;
        while (input >> value) data.emplace_back(value);

        input.close();

        return data;
    }
}

namespace aoc::dbg {
    template<typename T>
    void dump(std::vector<T> v) {
        for (const auto& item : v) std::cout << item << std::endl;
    }

    template<typename K, typename V>
    void dump(std::map<K, V> m) {
        for (const auto&[key, value] : m) std::cout << key << ":" << value << std::endl;
    }

    template<typename T>
    void dump(std::set<T> s) {
        for (const auto& item : s) std::cout << item << std::endl;
    }

    template<typename T>
    void dump(std::deque<T> q) {
        for (const auto& item : q) std::cout << item << std::endl;
    }
}

namespace ansiterm {
    void clear();
    void moveTo(const int x, const int y);
    void writeAt(const int x, const int y, const std::string& text);
    void writeAt(const int x, const int y, long l);
    void writeAt(const int x, const int y, const char& c);
    void writeAt(const Pos& pos, const char& c);
    void writeAt(const Pos& pos, const std::string& text);
    void hideCursor();
    void showCursor();
    void showCursor(bool);

#define MAKE_MANIPULATOR(name, code)                               \
  template < typename CharT, typename Traits = std::char_traits<CharT> > \
  inline std::basic_ostream< CharT, Traits >&                            \
  name(std::basic_ostream< CharT, Traits >& os)                          \
  { return os << code; }

    namespace manip {
//        std::ostream &moveto(const int x, const int y)
        MAKE_MANIPULATOR(clear, "\x1b[2J")
        MAKE_MANIPULATOR(cursor_off, "\x1b[?25l")
        MAKE_MANIPULATOR(cursor_on, "\x1b[?25h")
        MAKE_MANIPULATOR(reset, "\x1b[00m")
        MAKE_MANIPULATOR(bold, "\x1b[1m")
        MAKE_MANIPULATOR(dark, "\x1b[2m")
        MAKE_MANIPULATOR(italic, "\x1b[3m")
        MAKE_MANIPULATOR(underline, "\x1b[4m")
        MAKE_MANIPULATOR(blink, "\x1b[5m")
        MAKE_MANIPULATOR(reverse, "\x1b[7m")
        MAKE_MANIPULATOR(concealed, "\x1b[8m")
        MAKE_MANIPULATOR(crossed, "\x1b[9m")
//TODO
//        template<typename CharT, typename Traits = std::char_traits<CharT> >
//        inline std::basic_ostream<CharT, Traits>&
//        moveto(std::basic_ostream<CharT, Traits>& os, const int x, const int y) {
//            return os << "\x1b[" << y + 1 << ";" << x + 1 << "H" << std::flush;
//        }
    }

    namespace color {

#define MAKE_MANIPULATOR_COLOR(name, code)                               \
  template < typename CharT, typename Traits = std::char_traits<CharT> > \
  inline std::basic_ostream< CharT, Traits >&                            \
  name(std::basic_ostream< CharT, Traits >& os)                          \
  { return os << code; }

// These color definitions are based on the color scheme used by Git (the
// distributed version control system) as declared in the file
// `git/color.h`. You can add more manipulators as desired.

        MAKE_MANIPULATOR(normal, "")
        MAKE_MANIPULATOR(reset, "\x1b[m")
        MAKE_MANIPULATOR(bold, "\x1b[1m")
        MAKE_MANIPULATOR(red, "\x1b[31m")
        MAKE_MANIPULATOR(green, "\x1b[32m")
        MAKE_MANIPULATOR(yellow, "\x1b[33m")
        MAKE_MANIPULATOR(blue, "\x1b[34m")
        MAKE_MANIPULATOR(magenta, "\x1b[35m")
        MAKE_MANIPULATOR(cyan, "\x1b[36m")
        MAKE_MANIPULATOR(bold_red, "\x1b[1;31m")
        MAKE_MANIPULATOR(bold_green, "\x1b[1;32m")
        MAKE_MANIPULATOR(bold_yellow, "\x1b[1;33m")
        MAKE_MANIPULATOR(bold_blue, "\x1b[1;34m")
        MAKE_MANIPULATOR(bold_magenta, "\x1b[1;35m")
        MAKE_MANIPULATOR(bold_cyan, "\x1b[1;36m")
        MAKE_MANIPULATOR(bg_red, "\x1b[41m")
        MAKE_MANIPULATOR(bg_green, "\x1b[42m")
        MAKE_MANIPULATOR(bg_yellow, "\x1b[43m")
        MAKE_MANIPULATOR(bg_blue, "\x1b[44m")
        MAKE_MANIPULATOR(bg_magenta, "\x1b[45m")
        MAKE_MANIPULATOR(bg_cyan, "\x1b[46m")
    }
}
