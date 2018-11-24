#ifndef PTR_CURSOR_H
#define PTR_CURSOR_H

#include <list>
#include "cursor.h"
#include "buffer_type.h"


namespace VM {
    struct PtrCursor: public Cursor {
        VM::BufferType &buffer;
        bool canPointAfterLastCharacterInLine;
        bool canWrapBetweenTheLines;

        PtrCursor(const Cursor &cursor, BufferType &buffer);
        PtrCursor(const Cursor &cursor, BufferType &buffer, bool canPointAfterLastCharacterInLine, bool canWrapBetweenTheLines);
        std::string::iterator getStringIterator();
        BufferType::iterator getLineIterator();
        void moveRight();
        void moveRight(int c);
        void moveLeft();
        void moveLeft(int c);
        bool isEOF();
        bool isLastPositionInLine();
    };
}

#endif
