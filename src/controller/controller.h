#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mode/lazy_command_mode/colon_command_mode.h"
#include "mode/insert_mode.h"
#include "mode/command_mode.h"
#include <memory>
#include <stack>


namespace VM {
    class Input;
    class FileBuffer;

    class Controller {
        typedef std::stack<std::unique_ptr<UndoableCommand>> CommandStack;

        std::unique_ptr<Input> input; 
        FileBuffer *fileBuffer;
        CommandStack undoStack;
        CommandStack redoStack;

        bool programIsRunning;

        struct Modes {
            InsertMode insertMode;
            CommandMode commandMode;
            ColonCommandMode colonCommandMode;
            
            Modes(Controller &controller):
                insertMode{controller},
                commandMode{controller},
                colonCommandMode{controller}
            {}
        };

        public:
        Modes modes;

        private:
        Mode *mode;

        public:
        void getAndProcessChar();
        Input* getInput() const {return input.get();}
        void changeMode(Mode *newMode) {mode = newMode;}
        Mode &getMode() {return *mode;}
        void changeBuffer(FileBuffer *newFileBuffer) {fileBuffer = newFileBuffer;}
        FileBuffer &getBuffer() {return *fileBuffer;}
        CommandStack &getUndoStack() {return undoStack;}
        CommandStack &getRedoStack() {return redoStack;}

        void quit(bool ignoreChanges);
        operator bool() const {return programIsRunning;}

        Controller(std::unique_ptr<Input> input, FileBuffer *fileBuffer);
        Controller(const Controller &other) = delete;
    };
}

#endif
