#include <fstream>
#include "file_buffer.h"


namespace VM {
    FileBuffer::FileBuffer():
        buffer{},
        ptrCursor{Cursor {0, 0}, buffer}
    {}

    FileBuffer::FileBuffer(const std::string &fileName):
        buffer{},
        ptrCursor{Cursor {0, 0}, buffer}
    {
        std::ifstream file {fileName};
        std::string temp;
        while(std::getline(file, temp)) {
            buffer.push_back(std::move(temp)); 
        }
    }

    void FileBuffer::type(char a) {
        ptrCursor.linePosn->insert(ptrCursor.charPosn, a);
        ++ptrCursor.charPosn;
    }

    void FileBuffer::type(char a, const Cursor &cursor) {
        buffer[cursor.line].insert(cursor.col, std::string {a});
    }

    void FileBuffer::type(const std::string &s, const Cursor &cursor) {
        buffer[cursor.line].insert(cursor.col, s);
    }

    void FileBuffer::delete_forward(int numChars) {
        ptrCursor.linePosn->erase(ptrCursor.col, numChars);
    }

    void FileBuffer::delete_forward(int numChars, const Cursor &cursor) {
        buffer[cursor.line].erase(cursor.col, numChars);
    }

    void FileBuffer::delete_backward(int numChars) {
        ptrCursor.charPosn -= numChars;
        ptrCursor.col -= numChars;
        ptrCursor.linePosn->erase(ptrCursor.col, numChars);
    }

    void FileBuffer::delete_backward(int numChars, const Cursor &cursor) {
        buffer[cursor.col].erase(cursor.col-numChars, numChars);
    }
}
