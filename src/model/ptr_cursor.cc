#include "ptr_cursor.h"
#include "buffer_type.h"
#include <cassert>

namespace  VM {
    PtrCursor::PtrCursor(const VM::Cursor &cursor, VM::BufferType &buffer,
                         bool canPointAfterLastCharacterInLine)
    : Cursor(cursor), buffer(buffer), canPointAfterLastCharacterInLine(canPointAfterLastCharacterInLine)
    {
        assert(buffer.size()>0);
        if(line >= buffer.size()) {
            line = buffer.size() - 1;
            col = buffer[line].size();
        }
        if(col >= buffer[line].size()) col = buffer[line].size();
        if(!canPointAfterLastCharacterInLine && col != 0) --col;
    }
    PtrCursor::PtrCursor(const VM::Cursor &cursor, VM::BufferType &buffer) :  PtrCursor(cursor,buffer, true) {} // FIXME: should depend on the mode!
    void PtrCursor::moveLeft() {moveLeft(1);}
    void PtrCursor::moveLeft(size_t c) {
        col = (size_t) std::max(0, (int)col - (int)c);
    }

    void PtrCursor::moveRight() {moveRight(1);}
    void PtrCursor::moveRight(size_t c) {
        col = std::min(col + c, buffer[line].size() + canPointAfterLastCharacterInLine - 1 );
    }
    void PtrCursor::moveDown(size_t c) {line = std::min(buffer.size()-1, line + c);}
    void PtrCursor::moveDown() {moveDown(1);}
    void PtrCursor::moveUp(size_t c) {line = (size_t)std::max(0, (int) line- (int)c);}
    void PtrCursor::moveUp() {moveUp(1);}

    void PtrCursor::setCursor(const Cursor &posn) {
        if(posn.line > line) {
            moveDown(posn.line - line);
            moveRight(0);
        }
        else if(posn.line < line) {
            moveUp(line - posn.line);
            moveRight(0);
        }

        if(posn.col > col) {
            moveRight(posn.col - col);
        }
        else if(posn.col < col) {
            moveLeft(col - posn.col);
        }
    }

    LineType::iterator PtrCursor::getStringIterator() const {
        return buffer[line].begin()+col;
    }
    LineType::reverse_iterator PtrCursor::getReverseStringIterator() const {
        return buffer[line].rbegin() + (buffer[line].size()-1 - col);
    }
    BufferType::iterator PtrCursor::getLineIterator() const {
        return buffer.begin()+line;
    }
    BufferType::reverse_iterator PtrCursor::getReverseLineIterator() const {
        return buffer.rbegin() + (buffer.size()-1 - line);
    }

    bool PtrCursor::isLastPositionInLine() {
        return buffer[line].size() - !canPointAfterLastCharacterInLine <= col;
    }
    bool PtrCursor::isEOF() {
        return (buffer.size()-1 == line && isLastPositionInLine());
    }
}
