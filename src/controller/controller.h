#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "insert_mode.h"
#include "command_mode.h"
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
            CommandMode commandMode;
            
            Modes(Controller &controller):
                insertMode{controller},
                commandMode{controller}
            {}
        };

        public:
        Modes modes;

        private:
        Mode *mode;

        public:
        bool getAndProcessChar(); // boolean indicator for if program should exit
        Input* getInput() const {return input.get();}
        void changeMode(Mode *newMode) {mode = newMode;}
        Mode &getMode() {return *mode;}
        void changeBuffer(FileBuffer *newFileBuffer) {fileBuffer = newFileBuffer;}
        FileBuffer &getBuffer() {return *fileBuffer;}

        Controller(std::unique_ptr<Input> input, FileBuffer *fileBuffer);
        Controller(const Controller &other) = delete;
    };
}

#endif
