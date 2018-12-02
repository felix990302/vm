#ifndef FILE_EXCEPTION_H
#define FILE_EXCEPTION_H

#include <string>

namespace VM {
    struct FileException {
        std::string filename;
    };
    struct FileReadException: public FileException {
        FileReadException(const std::string &filename) : FileException {filename} {}
    };
    struct FileWriteException: public FileException {
        FileWriteException(const std::string &filename) : FileException {filename} {}
    };
}

#endif
