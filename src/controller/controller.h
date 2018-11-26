#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mode/insert_mode.h"
#include "mode/command_mode.h"
#include <memory>
#include <stack>


namespace VM {
    class Input;
    class FileBuffer;

    class Controller {
        typedef std::stack<std::unique_ptr<Command>> CommandStack;

        std::unique_ptr<Input> input; 
        FileBuffer *fileBuffer;
        CommandStack undoStack;
        CommandStack redoStack;

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
        CommandStack &getUndoStack() {return undoStack;}
        CommandStack &getRedoStack() {return redoStack;}

        Controller(std::unique_ptr<Input> input, FileBuffer *fileBuffer);
        Controller(const Controller &other) = delete;
    };
}

#endif
