#ifndef BUFFER_VIEW_H
#define BUFFER_VIEW_H

#include "cursor.h"


class FileBuffer;

namespace VM {
    class BufferView {
        FileBuffer *fileBuffer;
        Cursor cursor;
    };
}

#endif

