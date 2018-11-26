#include <ncurses.h>
#include "ncurses_input.h"


namespace VM {
    int NCursesInput::getChar() {
        return wgetch(stdscr);
    }

    NCursesInput::NCursesInput() {
        cbreak();
        noecho();
        keypad(stdscr, FALSE);
    } 
}
