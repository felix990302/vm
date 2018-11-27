#include <fstream>
#include "write_exception.h"
#include "file_buffer.h"


namespace VM {
    FileBuffer::FileBuffer():
        fileName{},
        buffer{1},
        ptrCursor{Cursor {0, 0}, buffer}
    {}

    FileBuffer::FileBuffer(const std::string &fileName, const BufferType &bufferBase):
        fileName{fileName},
        buffer{bufferBase},
        ptrCursor{Cursor {0, 0}, buffer}
    {}

    void FileBuffer::type(char a) {
        ptrCursor.getLineIterator()->insert(ptrCursor.getStringIterator(), a);
        ptrCursor.moveRight();
    }

    void FileBuffer::type(char a, const Cursor &cursor) {
        buffer[cursor.line].insert(cursor.col, std::string {a});
    }

    void FileBuffer::type(const std::string &s, const Cursor &cursor) {
        buffer[cursor.line].insert(cursor.col, s);
    }

    void FileBuffer::typeNewLine() {
        std::string nextLine = ptrCursor.getLineIterator()->substr(ptrCursor.col);

        ptrCursor.getLineIterator()->erase(ptrCursor.col);
        ptrCursor.moveDown();
        ptrCursor.col = 0; // TODO: make this a function?
        buffer.insert(ptrCursor.getLineIterator(), nextLine);
    }

    void FileBuffer::delete_forward(int numChars) {
        ptrCursor.getLineIterator()->erase(ptrCursor.col, numChars);
    }

    void FileBuffer::delete_forward(int numChars, const Cursor &cursor) {
        buffer[cursor.line].erase(cursor.col, numChars);
    }

    void FileBuffer::delete_backward(int) {
        /*ptrCursor.charPosn -= numChars;
        ptrCursor.col -= numChars;
        ptrCursor.linePosn->erase(ptrCursor.col, numChars);*/
    }

    void FileBuffer::delete_backward(int, const Cursor &) {
        //buffer[cursor.col].erase(cursor.col-numChars, numChars);
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
