#ifndef FILE_EXCEPTION_H
#define FILE_EXCEPTION_H

namespace VM {
    class FileException {};
    class FileReadException: public FileException {};
    class FileWriteException: public FileException {};
}

#endif
