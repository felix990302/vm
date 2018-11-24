#include "ptr_cursor.h"
#include "buffer_type.h"

namespace  VM {
    PtrCursor::PtrCursor(const VM::Cursor &cursor, VM::BufferType &buffer) : Cursor{cursor} {
        if(cursor.line >= buffer.size()) cursor.line = buffer.size()-1;
        if(cursor.col >= buffer[cursor.line].size()) cursor.col = buffer[cursor.line].size();
        linePosn = buffer.begin() + cursor.line;
        charPosn =  line.begin() + cursor.col;
    }
}