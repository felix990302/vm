#include "buffer_view.h"
#include "model/ptr_cursor.h"
#include "model/file_buffer.h"
#include <iostream>

namespace VM{
    void BufferView::draw(const Coordinates &, TextDisplay &display)
    {
        size_t newCursorY = cursor.line;
        size_t newCursorX = cursor.col;

        if(newCursorY > fileBuffer->ptrCursor.getLine())
            newCursorY = fileBuffer->ptrCursor.getLine();
        if(newCursorY + getSize().y - 1 <= fileBuffer -> ptrCursor.getLine())
            newCursorY = fileBuffer -> ptrCursor.getLine()-getSize().y + 1;

        if(newCursorX > fileBuffer->ptrCursor.getCol())
            newCursorX = fileBuffer->ptrCursor.getCol();
        if(newCursorX + getSize().x - 1 <= fileBuffer -> ptrCursor.getCol())
            newCursorX = fileBuffer -> ptrCursor.getCol() - getSize().x + 1;

        cursor = Cursor{newCursorY, newCursorX};


        for(int y = 0; y < getSize().y; ++y) {

            PtrCursor it(Cursor{cursor.line + y, cursor.col}, fileBuffer->getBuffer(), PtrCursor::CursorMovement::InsertModeCursor);
            display.flush(getPosn() + Coordinates{0, y});
            for (int x = 0; x < getSize().x; ++x) {
                display.putc(getPosn() + Coordinates{x, y}, *it);
                if(it.isEOL())
                    break;
                it.moveRight();
            }
        }
        display.setCursorPosition(fileBuffer->ptrCursor.getLine() - cursor.line, fileBuffer->ptrCursor.getCol() - cursor.col);

    }
    BufferView::BufferView(FileBuffer *fileBuffer) : cursor(0,0), fileBuffer(fileBuffer) {}
}
