#include <ncurses.h>
#include "ncurses_input.h"


namespace VM {
    int NCursesInput::getChar() {
        int c = getch();
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
