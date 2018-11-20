#ifndef BUFFER_VIEW_H
#define BUFFER_VIEW_H

#include "cursor.h"
#include "component.h"

class FileBuffer;

namespace VM {
    class BufferView : public Component {
    private:
        FileBuffer *fileBuffer;
        Cursor cursor;
    public:
        BufferView (FileBuffer * fileBuffer);
    };
}

#endif

