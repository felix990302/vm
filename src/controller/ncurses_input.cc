#include <ncurses.h>
#include "ncurses_input.h"


namespace VM {
    char NCursesInput::getChar() {
        return getch();
    }

    NCursesInput::NCursesInput() {
        raw();
        noecho();
        keypad(stdscr, TRUE);
    } 
}
