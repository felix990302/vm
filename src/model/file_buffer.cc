#include <fstream>
#include "write_exception.h"
#include "file_buffer.h"


namespace VM {
    FileBuffer::FileBuffer():
        fileName{},
        buffer{1},
        ptrCursor{Cursor {0, 0}, buffer, PtrCursor::CursorMovement::NormalModeCursor}
    {}

    FileBuffer::FileBuffer(const std::string &fileName, const BufferType &bufferBase):
        fileName{fileName},
        buffer{bufferBase},
        ptrCursor{Cursor {0, 0}, buffer, PtrCursor::CursorMovement::NormalModeCursor}
    {}

    void FileBuffer::type(char a) {
        if(a == '\n')
            typeNewLine();
        else
        {
            ptrCursor.getLineIterator()->insert(ptrCursor.getStringIterator(), a);
            ptrCursor.moveRight();
        }
    }

    void FileBuffer::type(const std::string &s) {
        for(size_t k=0; k<s.size(); ++k) type(s[k]);
    }


    void FileBuffer::typeWithinLine(const std::string &s) {
        ptrCursor.getLineIterator()->insert(ptrCursor.getCol(), s);
    }



    void FileBuffer::typeNewLine() {
        std::string nextLine = ptrCursor.getLineIterator()->substr(ptrCursor.getCol());
        ptrCursor.getLineIterator()->erase(ptrCursor.getCol());
        buffer.insert(++ptrCursor.getLineIterator(), nextLine); // ++ as it might point to end of file
        ptrCursor.moveDown();
        ptrCursor.moveBeginOfLine();
    }


    void FileBuffer::delete_forward(size_t numChars) {

        while (numChars > 0) {
            int inThisLine = std::min(ptrCursor.getLineIterator()->size() - ptrCursor.getCol(), numChars);
            ptrCursor.getLineIterator()->erase(ptrCursor.getCol(), numChars);
            numChars -= inThisLine;

            if (numChars > 0 && ptrCursor.getType() >= PtrCursor::CursorMovement::InsertModeCursor && !ptrCursor.isEOF()) {
                ptrCursor.getLineIterator()->append(std::move(*(++ptrCursor.getLineIterator())));
                buffer.erase(++ptrCursor.getLineIterator());
                --numChars;
            }
            else
                break;
        }
    }

    void FileBuffer::delete_backward(size_t numChars) {
        PtrCursor cur {ptrCursor};
        cur.moveLeft(numChars);
        size_t reallyRemoved = ptrCursor - cur;
        ptrCursor.setCursor(cur);
        delete_forward(reallyRemoved);
    }

    void FileBuffer::deleteLine(size_t numLines) {
        buffer.erase(ptrCursor.getLineIterator(), ptrCursor.getLineIterator()+numLines);
        ptrCursor.moveBeginOfLine();
    }

    std::string FileBuffer::getSubBuffer(size_t n) {
        return getSubBuffer(n, ptrCursor);
    }
    std::string FileBuffer::getSubBuffer(size_t n, const PtrCursor &ptrCursor1) {
        PtrCursor cur {ptrCursor1};
        cur.setType(PtrCursor::CursorMovement::IteratorCursor);

        std::string ans;
        while((n-ans.size()) > (cur.getLineIterator()->size() - cur.getCol())) ans += cur.getLineIterator()->substr(cur.getCol()) + "\n";
        ans += cur.getLineIterator()->substr(cur.getCol(), n-ans.size());

        return ans;
    }

    void FileBuffer::write(const std::string &destination) {
        std::ofstream file {destination};
        if(file) {
            for(const auto &line : buffer) {
                file << line << std::endl;
            }
        }
        else {
            throw FileWriteException {};
        }
    }
    void FileBuffer::write() {write(fileName);}

}
