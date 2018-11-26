#ifndef MOTION_H
#define MOTION_H

#include <memory>


namespace VM {
    class Cursor;
    class PtrCursor;

    struct Motion {
        virtual Cursor startPosition(const PtrCursor &cursor); // default to doing nothing
        virtual Cursor nextPosition(const PtrCursor &cursor) = 0;
        virtual std::unique_ptr<Motion> clone() = 0;

        virtual ~Motion() = 0;
    };
}

#endif
