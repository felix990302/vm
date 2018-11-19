#ifndef NCURSES_INPUT_H
#define NCURSES_INPUT_H

#include "input.h"


struct NCursesInput: public Input {
    char getChar() override;
};

#endif

