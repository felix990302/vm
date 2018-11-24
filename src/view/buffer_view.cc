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

            for(int x = 0; x < getSize().x; ++x)
            {
                PtrCursor it(Cursor {cursor.line + y, cursor.col + x}, fileBuffer->getBuffer());
                if (it.getStringIterator() == it.getLineIterator()->end()) break;
                display.putc(getPosn() + Coordinates{x,y}, *it.getStringIterator());
            }
        }
    }
    BufferView::BufferView(FileBuffer *fileBuffer) : fileBuffer(fileBuffer) {}
}
