#include <ncurses.h>
#include "ncurses_input.h"


namespace VM {
    int NCursesInput::getChar() {
        return getch();
    }

    NCursesInput::NCursesInput() {
        //raw();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
    } 
}
