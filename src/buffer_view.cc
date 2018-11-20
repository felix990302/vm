#include "buffer_view.h"
#include "ptr_cursor.h"
#include "file_buffer.h"

namespace VM{
    void BufferView::draw(const VM::Coordinates &parentPosn, const VM::TextDisplay &display)
    {
        cursor =  {max(min(fileBuffer->ptrCursor.line, cursor.line), cursor.line + getSize().y),
                   max(min(fileBuffer->ptrCursor.col , cursor.col ), cursor.col  + getSize().x)};

        for(int y = 0; y < getSize().y; ++y)
        {
            PtrCursor it(Cursor {cursor.line + y, cursor.col});
            for(int x = 0; x < getSize().x; ++x)
            {
                if (it.charPosn == it.linePosn.end()) break;
                display.putc(getPosn() + {x,y}, *it.charPosn);
            }
        }
    }
    BufferView::BufferView(FileBuffer *fileBuffer) : fileBuffer(fileBuffer) {}
}