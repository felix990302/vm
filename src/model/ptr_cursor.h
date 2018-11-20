#ifndef PTR_CURSOR_H
#define PTR_CURSOR_H

#include <list>
#include "cursor.h"
#include "buffer_type.h"


namespace VM {
    struct PtrCursor: public Cursor {
        BufferType::iterator linePosn;
        LineType::iterator charPosn;

        PtrCursor(const Cursor &cursor, BufferType &buffer);
    };
}

#endif
