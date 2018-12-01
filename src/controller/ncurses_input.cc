#include <ncurses.h>
#include "ncurses_input.h"
#include "view/n_curses_display.h"

namespace VM {
    int NCursesInput::getChar() {
        int c = getch();
        while(c == KEY_RESIZE) {
            NCursesDisplay::resizeHandler(0);
            c = getch();
        }
        c=c;
        return c;
//        return getch(); //TODO debug only
    }

    NCursesInput::NCursesInput() {
        raw();
        keypad(stdscr, TRUE);
        noecho();
    } 
}
