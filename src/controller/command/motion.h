#ifndef MOTION_H
#define MOTION_H


class Cursor;

namespace VM {
    struct Motion {
        virtual Cursor nextPosition(const Cursor &cursor) = 0;
    };
}

#endif
