#include <fstream>
#include "file_buffer.h"


namespace VM {
    FileBuffer::FileBuffer():
        buffer{1},
        ptrCursor{Cursor {0, 0}, buffer}
    {

    }

    FileBuffer::FileBuffer(const std::string &fileName):
        buffer{1},
        ptrCursor{Cursor {0, 0}, buffer}
    {
        std::ifstream file {fileName};
        std::string temp;
        while(std::getline(file, temp)) {
            buffer.push_back(std::move(temp)); 
        }
    }

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
        std::string first = ptrCursor.getLineIterator()->substr(0, ptrCursor.col);
        std::string second = ptrCursor.getLineIterator()->substr(ptrCursor.col);

        *ptrCursor.getLineIterator() = second;
        buffer.insert(ptrCursor.getLineIterator(), first);

        ptrCursor.moveDown();
        ptrCursor.moveBeginOfLine();
    }

    void FileBuffer::delete_forward(int numChars) {
        ptrCursor.getLineIterator()->erase(ptrCursor.col, numChars);
    }

    void FileBuffer::delete_forward(int numChars, const Cursor &cursor) {
        buffer[cursor.line].erase(cursor.col, numChars);
    }

    void FileBuffer::delete_backward(int numChars) {
        /*ptrCursor.charPosn -= numChars;
        ptrCursor.col -= numChars;
        ptrCursor.linePosn->erase(ptrCursor.col, numChars);*/
    }

    void FileBuffer::delete_backward(int numChars, const Cursor &cursor) {
        //buffer[cursor.col].erase(cursor.col-numChars, numChars);
    }
}
