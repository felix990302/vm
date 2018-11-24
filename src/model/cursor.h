#ifndef CURSOR_H
#define CURSOR_H

#include <cstddef>


namespace VM {
    struct Cursor {
        size_t line;
        size_t col;

        Cursor(size_t line, size_t col);
    };
}

#endif
