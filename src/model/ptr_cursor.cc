#include "ptr_cursor.h"
#include "buffer_type.h"

namespace  VM {
    PtrCursor::PtrCursor(const VM::Cursor &cursor, VM::BufferType &buffer) : Cursor(cursor), buffer(buffer) {
        if(line >= buffer.size()) line = buffer.size()-1;
        if(col >= buffer[cursor.line].size()) col = buffer[line].size();
    }
    void PtrCursor::moveLeft() {col--;}
    void PtrCursor::moveLeft(int c) {col--; }
    void PtrCursor::moveRight() {col++; }
    void PtrCursor::moveRight(int c) {col+=c;}
    std::string::iterator PtrCursor::getStringIterator() {
        return buffer[line].begin()+col;
    }
    BufferType::iterator PtrCursor::getLineIterator() {
        return buffer.begin()+line;
    }
}