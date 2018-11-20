#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

#include <memory>
#include <list>
#include <string>
#include "ptr_cursor.h"
#include "buffer_base.h"


class BufferBase;

namespace VM {
    class FileBuffer final {
        PtrCursor ptrCursor;
        BufferBase bufferBase;

        public:
        void type(char a);
        void type(const std::string &s);
        void delete_forward(int numChars);
        void delete_backward(int numChars);

        FileBuffer();
        FileBuffer(const PtrCursor &ptrCursor);
        FileBuffer(const FileBuffer &other);
        FileBuffer(const FileBuffer &&other);
        FileBuffer &operator=(FileBuffer other);
    };
}

#endif

