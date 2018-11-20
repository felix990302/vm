#include <csignal>
#include "n_curses_display.h"

namespace VM {


    NCursesDisplay::NCursesDisplay() : TextDisplay() {
        initscr();
        signal(SIGWINCH, NCursesDisplay::resizeHandler);
    }

    void NCursesDisplay::putc(const Coordinates &c, char ch) {
        mvwaddch(stdscr, c.y, c.x, ch);
    }

    void NCursesDisplay::puts(const Coordinates &c, const std::string &s) {
        mvwaddstr(stdscr, c.y, c.x, s.c_str());
    }

    void NCursesDisplay::redraw() {
        TextDisplay::redraw();
        wrefresh(stdscr);
    }

    void NCursesDisplay::resizeHandler(int)
    {
        int nh, nw;
        getmaxyx(stdscr, nh, nw);
        ((TextDisplay *)&NCursesDisplay::mainDisplay)->resizeHandler(Coordinates {nw, nh});
        NCursesDisplay::mainDisplay.redraw();
    }

    NCursesDisplay &NCursesDisplay::getMainDisplay() {
        return mainDisplay;
    }

    NCursesDisplay NCursesDisplay::mainDisplay = NCursesDisplay();

}