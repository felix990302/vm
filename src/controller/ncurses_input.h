#ifndef NCURSES_INPUT_H
#define NCURSES_INPUT_H

#include "input.h"


namespace VM {
    struct NCursesInput: public Input {
        int getChar() override;
        NCursesInput();
        NCursesInput(const NCursesInput &other) = delete;
        NCursesInput &operator=(const NCursesInput &other) = delete;
    };
}

#endif

