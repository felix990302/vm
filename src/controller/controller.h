#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>


namespace VM {
    class Input;
    class Mode;
    class FileBuffer;

    class Controller {
        std::unique_ptr<Input> input; 
        Mode *mode;
        FileBuffer *fileBuffer;

        public:
        void getAndProcessChar();
        Input* const getInput() const;
        void changeMode(Mode *mode);
        void changeBuffer(FileBuffer *fileBuffer);
        FileBuffer* const getBuffer() const {return fileBuffer;}

        Controller(std::unique_ptr<Input> input, Mode *mode, FileBuffer *fileBuffer);
        Controller(const Controller &other) = delete;
    };
}

#endif
