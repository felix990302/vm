#ifndef MOTION_H
#define MOTION_H

#include <memory>


class Cursor;

namespace VM {
    struct Motion {
        virtual Cursor nextPosition(const Cursor &cursor) = 0;
        virtual std::unique_ptr<Motion> clone() = 0;
    };
}

#endif
