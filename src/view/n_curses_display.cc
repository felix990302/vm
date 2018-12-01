#include <csignal>
#include "n_curses_display.h"


namespace VM {
    NCursesDisplay::NCursesDisplay() : TextDisplay() {
        initscr();
        //signal(SIGWINCH, NCursesDisplay::resizeHandler);
    }

    void NCursesDisplay::putc(const Coordinates &c, char ch) {
        mvwaddch(stdscr, c.y, c.x, ch);
    }

    void NCursesDisplay::puts(const Coordinates &c, const std::string &s) {
        mvwaddstr(stdscr, c.y, c.x, s.c_str());
    }

    void NCursesDisplay::flush(const Coordinates &c) {
        setCursorPosition(c.y, c.x);
        wclrtoeol(stdscr); // TODO: investigate whether to reset cursor posn
    }

    void NCursesDisplay::redraw() {
        TextDisplay::redraw();
        wrefresh(stdscr);
    }

    void NCursesDisplay::resizeHandler(int)
    {
        int nh, nw;
        getmaxyx(stdscr, nh, nw);
        ((TextDisplay *)&NCursesDisplay::getMainDisplay())->resizeHandler(Coordinates {nw, nh});
        NCursesDisplay::getMainDisplay().redraw();
    }

    NCursesDisplay &NCursesDisplay::getMainDisplay() {
        static NCursesDisplay mainDisplay;
        return mainDisplay;
    }

    NCursesDisplay::~NCursesDisplay() {endwin();}

    void NCursesDisplay::setCursorPosition(size_t y, size_t x) {
        wmove(stdscr, y, x);
    }
}
