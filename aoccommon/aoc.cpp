#include "aoc.h"

bool Vec_T_IO::vec_style_2D = false;
char Vec_T_IO::vec_style_delim_open = '(';
char Vec_T_IO::vec_style_delim_close = ')';

namespace aoc {
    void sleepMS(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    bool isNumber(const std::string& s) {
        return !s.empty() && s.find_first_not_of("-0123456789") == std::string::npos;
    }

    void waitForKeypress(int intervalMS) {
        while (!aoc::_kbhit()) {
            aoc::sleepMS(200);
        }
    }
}

namespace ansiterm {

    void clear() { std::cout << manip::clear << std::flush; }
//    void setColour(ansiterm::manip m) {std::cout << m << std::flush};

    void moveTo(const int x, const int y) { std::cout << "\x1b[" << y + 1 << ";" << x + 1 << "H" << std::flush; }
//    void moveTo(const int x, const int y) { std::cout << manip::moveto(x,y) << std::flush; }

    void writeAt(const int x, const int y, const std::string& text) {
        moveTo(x, y);
        std::cout << text << std::flush;
    }

    void writeAt(const int x, const int y, long l) {
        moveTo(x, y);
        std::cout << l << std::flush;
    }

    void writeAt(const int x, const int y, const char& c) {
        moveTo(x, y);
        std::cout << c << std::flush;
    }

    void writeAt(const Pos& pos, const char& c) {
        writeAt(pos.x, pos.y, c);
    }

    void writeAt(const Pos& pos, const std::string& text) {
        writeAt(pos.x, pos.y, text);
    }

    void hideCursor() {
        std::cout << manip::cursor_off << std::endl;
    }

    void showCursor() {
        std::cout << manip::cursor_on << std::endl;
    }

    void showCursor(bool on) {
        if (on) showCursor(); else hideCursor();
    }
}

namespace aoc::io {
    std::string loadIntoString(const std::string& filename) {
        std::string data;

        std::ifstream in(filename);
        std::stringstream buffer;
        buffer << in.rdbuf();
        in.close();
        return buffer.str();
    }

    std::ostream& vecstyle_2d(std::ostream& os) {
        Vec_T_IO::vec_style_2D = true;
        return os;
    }

    std::ostream& vecstyle_3d(std::ostream& os) {
        Vec_T_IO::vec_style_2D = false;
        return os;
    }

    std::ostream& vecstyle_delim_angled(std::ostream& os) {
        Vec_T_IO::vec_style_delim_open = '<';
        Vec_T_IO::vec_style_delim_close = '>';
        return os;
    }

    std::ostream& vecstyle_delim_round(std::ostream& os) {
        Vec_T_IO::vec_style_delim_open = '(';
        Vec_T_IO::vec_style_delim_close = ')';
        return os;
    }
}

Vec headingForChar(char c) {
    if (c == '^') return Vec(0, -1);
    if (c == '>') return Vec(1, 0);
    if (c == 'v') return Vec(0, 1);
//    if (c == '<')
    return Vec(-1, 0);
}

char charForHeading(const Vec& heading) {
    if (heading == Vec(0, -1)) return '^';
    if (heading == Vec(1, 0)) return '>';
    if (heading == Vec(0, 1)) return 'v';
//    if (heading == Vec(-1, 0))
    return '<';
}

#ifdef __linux__
/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <termios.h>

namespace aoc {
    int _kbhit() {
        static bool initialized = false;

        if (!initialized) {
            // Use termios to turn off line buffering
            termios term;
            tcgetattr(0, &term);
            term.c_lflag &= (~ICANON | ECHO);
            tcsetattr(0, TCSANOW, &term);
            setbuf(stdin, NULL);
            initialized = true;
        }

        int bytesWaiting;
        ioctl(0, FIONREAD, &bytesWaiting);
        tcflush(0, TCIFLUSH); // clear stdin
        return bytesWaiting;
    }
}
#endif

#ifdef X11
#include <X11/Xlib.h>
#include <iostream>
#include "X11/keysym.h"

/**
 *
 * @param ks  like XK_Shift_L, see /usr/include/X11/keysymdef.h
 * @return
 */
bool key_is_pressed(KeySym ks) {
    Display *dpy = XOpenDisplay(":0");
    char keys_return[32];
    XQueryKeymap(dpy, keys_return);
    KeyCode kc2 = XKeysymToKeycode(dpy, ks);
    bool isPressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
    XCloseDisplay(dpy);
    return isPressed;
}
#endif


//#include <iostream>
//#include <sys/select.h>
//
//int kbhit(void) {
//    struct timeval tv;
//    fd_set read_fd;
//
//    /* Do not wait at all, not even a microsecond */
//    tv.tv_sec = 0;
//    tv.tv_usec = 0;
//
//    /* Must be done first to initialize read_fd */
//    FD_ZERO(&read_fd);
//
//    /* Makes select() ask if input is ready:
//     * 0 is the file descriptor for stdin    */
//    FD_SET(0, &read_fd);
//
//    /* The first parameter is the number of the
//     * largest file descriptor to check + 1. */
//    if (select(1, &read_fd, NULL, /*No writes*/NULL, /*No exceptions*/&tv) == -1)
//        return 0;  /* An error occured */
//
//    /*  read_fd now holds a bit map of files that are
//     * readable. We test the entry for the standard
//     * input (file 0). */
//
//    if (FD_ISSET(0, &read_fd))
//        /* Character pending on stdin */
//        return 1;
//
//    /* no characters were pending */
//    return 0;
//}
