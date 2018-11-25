#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "insert_mode.h"
#include <memory>


namespace VM {
    class Input;
    class Mode;
    class InsertMode;
    class FileBuffer;

    class Controller {
        std::unique_ptr<Input> input; 
        FileBuffer *fileBuffer;

        struct Modes {
            InsertMode insertMode;
            
            Modes(Controller &controller): insertMode{controller} {}
        };

        public:
        Modes modes;

        private:
        Mode *mode;

        public:
        bool getAndProcessChar(); // boolean indicator for if program should exit
        Input* const getInput() const {return input.get();}
        void changeMode(Mode *newMode) {mode = newMode;}
        void changeBuffer(FileBuffer *newFileBuffer) {fileBuffer = newFileBuffer;}
        FileBuffer* const getBuffer() const {return fileBuffer;}

        Controller(std::unique_ptr<Input> input, FileBuffer *fileBuffer);
        Controller(const Controller &other) = delete;
    };
}

#endif
