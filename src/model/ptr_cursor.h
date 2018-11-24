#ifndef PTR_CURSOR_H
#define PTR_CURSOR_H

#include <list>
#include "cursor.h"
#include "buffer_type.h"


namespace VM {
    struct PtrCursor: public Cursor {
        PtrCursor(const Cursor &cursor, BufferType &buffer);
        VM::BufferType &buffer;
        std::string::iterator getStringIterator();
        BufferType::iterator getLineIterator();
        void moveRight();
        void moveRight(int c);
        void moveLeft();
        void moveLeft(int c);
    };
}

#endif
