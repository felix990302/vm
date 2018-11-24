#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

#include <memory>
#include <string>
#include "ptr_cursor.h"
#include "buffer_type.h"



namespace VM {
    class FileBuffer {
        BufferType buffer;

    public:
        PtrCursor ptrCursor;

        FileBuffer();
        FileBuffer(const std::string &fileName);

        void type(char a);
        void type(char a, const Cursor &cursor);

        void type(const std::string &s);
        void type(const std::string &s, const Cursor &cursor);

        void delete_forward(int numChars);
        void delete_forward(int numChars, const Cursor &cursor);

        void delete_backward(int numChars);
        void delete_backward(int numChars, const Cursor &cursor);

        BufferType &getBuffer() {
            return buffer;
        }
    };
}

#endif

