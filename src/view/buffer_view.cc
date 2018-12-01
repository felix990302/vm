#include "buffer_view.h"
#include "model/ptr_cursor.h"
#include "model/file_buffer.h"
#include <iomanip>
#include <iostream>


namespace VM{
    void BufferView::draw(const Coordinates &, TextDisplay &display)
    {
        int lineNumberWidth = showLinesNumbers * (std::max(std::to_string(fileBuffer->getBuffer().size()).size(), (size_t) 3) + 1);
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
            display.flush(getPosn() + Coordinates{lineNumberWidth, y});
            for (int x = 0; x < getSize().x; ++x) {
                display.putc(getPosn() + Coordinates{lineNumberWidth + x, y}, *it);
                if(it.isEOL())
                    break;
                it.moveRight();
            }
        }
        for(int y = 0; y < getSize().y; ++y)
        {
            std::stringstream ss;
            //ss << std::setw(getSize().x-left.size())<< std::right << (right + "    " + coordinates  + "\t");
            if(cursor.line + y >= fileBuffer->getBuffer().size())
                ss << "~";
            else
                if(showLinesNumbers)
                    ss  << std::setw(lineNumberWidth - 1) << std::right  << cursor.line + y + 1 << " ";
            display.puts(Coordinates{0,y}, ss.str());
        }
        display.setCursorPosition(fileBuffer->ptrCursor.getLine() - cursor.line, lineNumberWidth + fileBuffer->ptrCursor.getCol() - cursor.col);

    }
    BufferView::BufferView(FileBuffer *fileBuffer) : cursor(0,0), fileBuffer(fileBuffer) {}
}
