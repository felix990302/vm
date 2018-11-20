#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

#include <memory>
#include <list>
#include <string>
#include "ptr_cursor.h"
#include "buffer_type.h"



namespace VM {
    class FileBuffer {
        std::unique_ptr<BufferType> buffer;

    public:
        PtrCursor ptrCursor;

        FileBuffer();
        void type(char a);
        void type(const std::string &s);
        void delete_forward(int numChars);
        void delete_backward(int numChars);

        BufferType &getBuffer() {
            return *buffer;
        }
    };
}

#endif

