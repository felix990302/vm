#include "buffer_view.h"
#include "model/ptr_cursor.h"
#include "model/file_buffer.h"
#include <iostream>

namespace VM{
    void BufferView::draw(const Coordinates &parentPosn, TextDisplay &display)
    {

        cursor =  {(size_t) std::max((int) std::min(fileBuffer->ptrCursor.line, cursor.line) - getSize().y, (int) cursor.line ),
                   (size_t) std::max((int) std::min(fileBuffer->ptrCursor.col , cursor.col ) - getSize().x, (int) cursor.col  )};



        for(int y = 0; y < getSize().y; ++y)
        {

            for(int x = 0; x < getSize().x; ++x)
            {
                PtrCursor it(Cursor {cursor.line + y, cursor.col + x}, fileBuffer->getBuffer(), true, false);
                if (it.getStringIterator() == it.getLineIterator()->end()) break;
                display.putc(getPosn() + Coordinates{x,y}, *it.getStringIterator());
            }
        }
    }
    BufferView::BufferView(FileBuffer *fileBuffer) : cursor(0,0), fileBuffer(fileBuffer) {}
}
