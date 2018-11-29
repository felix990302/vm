#ifndef PTR_CURSOR_H
#define PTR_CURSOR_H

#include <list>
#include "cursor.h"
#include "buffer_type.h"


namespace VM {
    class PtrCursor{
    public:
        enum class CursorMovement{
            NormalModeCursor = 0,
            InsertModeCursor = 1,
            IteratorCursor = 2
        };
    private:
        Cursor cursor;
        VM::BufferType &buffer;

        CursorMovement type;

    public:
        bool wrapAtEOL() const { return (int)type >= 2;}
        bool canPointAtEOL() const { return (int) type >= 1 || (getLineIterator()->size() == 0);} //TODO: This is bug factorys

        PtrCursor(const Cursor &cursor, BufferType &buffer, const CursorMovement &type);


        inline void moveRight() {moveRight(1);}
        void moveRight(size_t c);
        inline void moveLeft() {moveLeft(1);}
        void moveLeft(size_t c);

        inline void enforceLineBoundaries()
        {
            cursor.col = std::min(cursor.col, getLineIterator()->size());
            if(getLineIterator()->size() != 0 && isEOL() && !canPointAtEOL()) --cursor.col;
        }

        inline void moveDown(size_t c) {cursor.line = std::min(buffer.size()-1, cursor.line + c);enforceLineBoundaries();}
        inline void moveDown() {moveDown(1);}
        inline void moveUp(size_t c) {cursor.line = (size_t)std::max(0, (int) cursor.line - (int)c);enforceLineBoundaries();}
        inline void moveUp() {moveUp(1);}
        inline void setType(const CursorMovement &c) {
            type = c;
            enforceLineBoundaries();
        }
        inline CursorMovement getType()
        {
            return type;
        }
        void setCursor(const Cursor &posn);


        int operator-(const PtrCursor &ptrCursor) const;
        bool operator<(const PtrCursor &ptrCursor) const;
        operator Cursor() const { return cursor; }

        inline LineType::iterator getStringIterator() const {
            return buffer[cursor.line].begin()+cursor.col;
        }
        inline LineType::reverse_iterator getReverseStringIterator() const {
            return buffer[cursor.line].rbegin() + (buffer[cursor.line].size()-1 - cursor.col);
        }
        inline BufferType::iterator getLineIterator() const {
            return buffer.begin()+cursor.line;
        }
        inline BufferType::iterator getLineBegin() const {
            return buffer.begin();
        }
        inline BufferType::iterator getLineEnd() const {
            return buffer.end();
        }
        inline BufferType::reverse_iterator getReverseLineIterator() const {
            return buffer.rbegin() + (buffer.size()-1 - cursor.line);
        }
        inline BufferType::reverse_iterator getLineReverseBegin() const {
            return buffer.rbegin();
        }
        inline BufferType::reverse_iterator getLineReverseEnd() const {
            return buffer.rend();
        }

        inline bool isEOL() const{
            return buffer[cursor.line].size() <= cursor.col;
        }
        inline bool isEOF() const{
            return (buffer.size()-1 == cursor.line && isEOL());
        }

        inline void moveBeginOfLine() {
            cursor.col = 0;
        }
        inline void moveEndOfLine() {
            cursor.col = buffer[cursor.line].size() + canPointAtEOL() - 1;
        }

        inline size_t getLine() const {
            return cursor.line;
        }

        inline size_t getBufferSize() const {
            return buffer.size();
        }

        inline size_t getCol() const {
            return cursor.col;
        }

        inline const Cursor & getCursor() const {
            return cursor;
        }

        inline PtrCursor & operator++() {
            moveRight();
            return *this;
        }

        inline PtrCursor &operator--() {
            moveLeft();
            return *this;
        }

        inline char operator*() const {
            return canPointAtEOL()&&isEOL()?'\n': *getStringIterator();
        }
    };
}

#endif
