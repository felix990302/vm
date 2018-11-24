#include "ptr_cursor.h"
#include "buffer_type.h"

namespace  VM {
    PtrCursor::PtrCursor(const VM::Cursor &cursor, VM::BufferType &buffer) : Cursor{cursor} {
        if(line >= buffer.size()) line = buffer.size()-1;
        if(col >= buffer[cursor.line].size()) col = buffer[line].size();
        linePosn = buffer.begin() + cursor.line;
        charPosn =  linePosn->begin() + cursor.col;
    }
}