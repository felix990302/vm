#include "ptr_cursor.h"
#include "buffer_type.h"
#include <cassert>

namespace  VM {
    PtrCursor::PtrCursor(const VM::Cursor &cursor1, VM::BufferType &buffer,
                         const VM::PtrCursor::CursorMovement &type = VM::PtrCursor::CursorMovement::IteratorCursor )
    : cursor(cursor1), buffer(buffer), type(type)
    {
        assert(buffer.size()>0);
        if(cursor.line >= buffer.size()) {
            cursor.line = buffer.size() - 1;
            cursor.col = buffer[cursor.line].size();
        }
        if(cursor.col >= buffer[cursor.line].size()) cursor.col = buffer[cursor.line].size();
        if(!canPointAtEOL() && cursor.col != 0) --cursor.col;
    }

    void PtrCursor::moveLeft(size_t c) {
        while(c > 0)
        {
            size_t maxMoveLeft = std::min(c, cursor.col);
            c -= maxMoveLeft;
            cursor.col -= maxMoveLeft;
            if(!wrapAtEOL() || c==0 || cursor.line == 0) return;
            moveUp();
            moveEndOfLine();
            --c;
        }
    }


    void PtrCursor::moveRight(size_t c) {
        while(c > 0)
        {
            size_t maxMoveRight = std::min(c, buffer[cursor.line].size() + canPointAtEOL() - 1 - cursor.col);
            c -= maxMoveRight;
            cursor.col += maxMoveRight;
            if(!wrapAtEOL() || c==0 || cursor.line == buffer.size()-1) return;
            moveDown();
            moveBeginOfLine();
            --c;
        }
    }



    void PtrCursor::setCursor(const Cursor &posn) {
        VM::PtrCursor::CursorMovement tmp = type;
        type = VM::PtrCursor::CursorMovement::IteratorCursor;
        if(posn.line > cursor.line) {
            moveDown(posn.line - cursor.line);
            moveRight(0);
        }
        else if(posn.line < cursor.line) {
            moveUp(cursor.line - posn.line);
            moveRight(0);
        }

        if(posn.col > cursor.col) {
            moveRight(posn.col - cursor.col);
        }
        else if(posn.col < cursor.col) {
            moveLeft(cursor.col - posn.col);
        }
        type = tmp;
    }



    int PtrCursor::operator-(const PtrCursor &ptrCursor) const {
        if(operator<(ptrCursor))
            return ptrCursor-*this;


        const PtrCursor &lower = ptrCursor;
        PtrCursor higher = *this;

        higher.type = PtrCursor::CursorMovement::IteratorCursor;
        int ans = 0;
        while (higher.cursor.line > lower.cursor.line)
        {
            ans += higher.cursor.col + 1;
            higher.moveUp();
            higher.moveEndOfLine();
        }
        return ans + higher.cursor.col - lower.cursor.col;
    }

    bool PtrCursor::operator<(const PtrCursor &ptrCursor) const {
        if(cursor.line < ptrCursor.cursor.line) return true;
        if(cursor.line > ptrCursor.cursor.line) return false;
        return cursor.col<ptrCursor.cursor.col;
    }
}
