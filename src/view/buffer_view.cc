#include "buffer_view.h"
#include "model/ptr_cursor.h"
#include "model/file_buffer.h"

namespace VM{
    void BufferView::draw(const Coordinates &parentPosn, TextDisplay &display)
    {
        cursor =  {std::max(std::min(fileBuffer->ptrCursor.line, cursor.line), cursor.line + getSize().y),
                   std::max(std::min(fileBuffer->ptrCursor.col , cursor.col ), cursor.col  + getSize().x)};

        for(int y = 0; y < getSize().y; ++y)
        {
            PtrCursor it(Cursor {cursor.line + y, cursor.col}, fileBuffer->getBuffer());
            for(int x = 0; x < getSize().x; ++x)
            {
                if (it.charPosn == it.linePosn->end()) break;
                display.putc(getPosn() + Coordinates{x,y}, *it.charPosn);
            }
        }
    }
    BufferView::BufferView(FileBuffer *fileBuffer) : fileBuffer(fileBuffer) {}
}
