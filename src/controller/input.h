#ifndef INPUT_H
#define INPUT_H

namespace VM {
    struct Input {
        virtual char getChar() = 0;
    };
}

#endif
