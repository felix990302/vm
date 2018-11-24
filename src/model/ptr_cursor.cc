#include "ptr_cursor.h"
#include "buffer_type.h"

namespace  VM {
    PtrCursor::PtrCursor(const VM::Cursor &cursor, VM::BufferType &buffer,
                         bool canPointAfterLastCharacterInLine, bool canWrapBetweenTheLines)
    : Cursor(cursor), buffer(buffer), canPointAfterLastCharacterInLine(canPointAfterLastCharacterInLine),
    canWrapBetweenTheLines(canWrapBetweenTheLines)
    {
        if(line >= buffer.size()) {line = buffer.size() - 1; col = buffer[line].size();}
        if(col >= buffer[cursor.line].size()) col = buffer[line].size();
        if(!canPointAfterLastCharacterInLine) --col;
    }
    PtrCursor::PtrCursor(const VM::Cursor &cursor, VM::BufferType &buffer) :  PtrCursor(cursor,buffer, false, false) {}
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

    bool PtrCursor::isLastPositionInLine() {
        return buffer[line].size() - !canPointAfterLastCharacterInLine <= col;
    }
    bool PtrCursor::isEOF() {
        return (buffer.size()-1 == line && isLastPositionInLine());
    }
}