#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>


namespace VM {
    class Input;
    class Mode;
    class FileBuffer;

    struct Controller {
        std::unique_ptr<Input> input; 
        Mode &mode;
        FileBuffer *fileBuffer;

        void getAndProcessChar();
        void changeBuffer(FileBuffer *fileBuffer);

        Controller(std::unique_ptr<Input> input, Mode &mode, FileBuffer *fileBuffer);
        Controller(const Controller &other) = delete;
    };
}

#endif
