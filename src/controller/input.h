#ifndef INPUT_H
#define INPUT_H

namespace VM {
    struct Input {
        virtual int getChar() = 0;
    };
}

#endif
