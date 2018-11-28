#ifndef MOTION_H
#define MOTION_H

#include <memory>
#include "utility/clonable.h"


namespace VM {
    class Cursor;
    class PtrCursor;

    struct Motion {
        size_t quantifier;

        virtual Cursor startPosition(const PtrCursor &cursor); // default to doing nothing
        virtual Cursor nextPosition(const PtrCursor &cursor) = 0;
        virtual std::unique_ptr<Motion> clone() const = 0;
        Motion (size_t quantifier);
        Motion ();

        virtual ~Motion() = 0;
    };

    template<typename Base, typename Sub> using ClonableMotion = Clonable<Motion, Base, Sub>;
}

#endif
