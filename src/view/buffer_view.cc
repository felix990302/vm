#include "buffer_view.h"
#include "model/ptr_cursor.h"
#include "model/file_buffer.h"
#include <iostream>

namespace VM{
    void BufferView::draw(const Coordinates &parentPosn, TextDisplay &display)
    {
        size_t newCursorY = cursor.line;
        size_t newCursorX = cursor.col;

        if(newCursorY > fileBuffer->ptrCursor.line)
            newCursorY = fileBuffer->ptrCursor.line;
        if(newCursorY + getSize().y - 1 <= fileBuffer -> ptrCursor.line)
            newCursorY = fileBuffer -> ptrCursor.line-getSize().y + 1;

        if(newCursorX > fileBuffer->ptrCursor.col)
            newCursorX = fileBuffer->ptrCursor.col;
        if(newCursorX + getSize().x - 1 <= fileBuffer -> ptrCursor.col)
            newCursorX = fileBuffer -> ptrCursor.col - getSize().x + 1;

        cursor = Cursor{newCursorY, newCursorX};


        for(int y = 0; y < getSize().y; ++y) {

            for (int x = 0; x < getSize().x; ++x) {
                PtrCursor it(Cursor{cursor.line + y, cursor.col + x}, fileBuffer->getBuffer(), true);
                if (it.getStringIterator() != it.getLineIterator()->end())
                    display.putc(getPosn() + Coordinates{x, y}, *it.getStringIterator());
                else {
                    display.flush(getPosn() + Coordinates{x, y});
                }
            }
        }
        display.setCursorPosition(fileBuffer->ptrCursor.line - cursor.line, fileBuffer->ptrCursor.col - cursor.col);

    }
    BufferView::BufferView(FileBuffer *fileBuffer) : cursor(0,0), fileBuffer(fileBuffer) {}
}
