#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

#include <memory>
#include <string>
#include "ptr_cursor.h"
#include "buffer_type.h"



namespace VM {
    class FileBuffer {
        std::string fileName;
        BufferType buffer;

    public:
        PtrCursor ptrCursor;

        FileBuffer();
        FileBuffer(const std::string &fileName, const BufferType &bufferBase);

        void type(char a);

        void type(const std::string &s);

        void typeNewLine();

        void delete_forward(size_t numChars);

        void delete_backward(size_t numChars);

        void deleteLine(size_t numLines=1);

        void write(const std::string &destination);
        void write();

        std::string getSubBuffer(size_t n);
        std::string getSubBuffer(size_t n, const PtrCursor &ptrCursor1); // not an accident

        void typeWithinLine(const std::string &s);

        BufferType &getBuffer() {
            return buffer;
        }
    };
}

#endif

