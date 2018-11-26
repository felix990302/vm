#ifndef PTR_CURSOR_H
#define PTR_CURSOR_H

#include <list>
#include "cursor.h"
#include "buffer_type.h"


namespace VM {
    struct PtrCursor: public Cursor {
        VM::BufferType &buffer;
        bool canPointAfterLastCharacterInLine;

        PtrCursor(const Cursor &cursor, BufferType &buffer);
        PtrCursor(const Cursor &cursor, BufferType &buffer, bool canPointAfterLastCharacterInLine);
        LineType::iterator getStringIterator() const;
        LineType::reverse_iterator getReverseStringIterator() const;
        BufferType::iterator getLineIterator() const;
        BufferType::reverse_iterator getReverseLineIterator() const;
        void moveRight();
        void moveRight(size_t c);
        void moveLeft();
        void moveLeft(size_t c);
        void moveDown();
        void moveDown(size_t c);
        void moveUp();
        void moveUp(size_t c);
        void setCursor(const Cursor &posn);

        void moveBeginOfLine();
        void moveEndOfLine();

        bool isEOF();
        bool isLastPositionInLine();
    };
}

#endif
