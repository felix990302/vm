#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <stack>
#include "controller/command/motion/direction.h"
#include "command/undoable_command.h"


namespace VM {
    class Input;
    class FileBuffer;
    class Mode;
    class InsertMode;
    class CommandMode;
    class ColonCommandMode;
    template<Direction dir>class SearchCommandMode;

    class Controller {
        typedef std::stack<std::unique_ptr<UndoableCommand>> CommandStack;

        std::unique_ptr<Input> input; 
        FileBuffer *fileBuffer;
        CommandStack undoStack;
        CommandStack redoStack;

        bool programIsRunning;

        struct Modes {
            std::unique_ptr<InsertMode> insertMode;
            std::unique_ptr<CommandMode> commandMode;
            std::unique_ptr<ColonCommandMode> colonCommandMode;
            std::unique_ptr<SearchCommandMode<Direction::DOWN>> searchDownMode;
            std::unique_ptr<SearchCommandMode<Direction::UP>> searchUpMode;
            
            Modes(Controller &controller);
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

        void runCommand(std::unique_ptr<Command> command);
        void pushCommand(std::unique_ptr<UndoableCommand> undoableCommand);

        void quit(bool ignoreChanges);
        operator bool() const {return programIsRunning;}

        Controller(std::unique_ptr<Input> input, FileBuffer *fileBuffer);
        Controller(const Controller &other) = delete;

        ~Controller();
    };
}

#endif
