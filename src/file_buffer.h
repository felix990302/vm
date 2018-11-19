#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

#include <memory>
#include <list>
#include <string>
#include "ptr_cursor.h"


class BufferBase;

namespace VM {
    class FileBuffer {
        PtrCursor ptrCursor;
        std::unique_ptr<BufferBase> bufferBase;

        public:
        void type(char a);
        void type(const std::string &s);
        void delete_forward(int numChars);
        void delete_backward(int numChars);
    };
}

#endif

