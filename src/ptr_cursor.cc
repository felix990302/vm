#include "ptr_cursor.h"
#include "buffer_type.h"

namespace  VM {
    PtrCursor::PtrCursor(const VM::Cursor &cursor, VM::BufferType &buffer) : Cursor{cursor} {
        linePosn = buffer.begin();
        for(size_t l = 0; l < line && (linePosn != buffer.end()); ++l, ++linePosn);
        if(linePosn == buffer.end())
            --linePosn, col = 0;//TODO dangerous
        charPosn = linePosn->begin();
        for(size_t c = 0; c < col && (charPosn != linePosn->end()); ++c, ++linePosn);
    }
}