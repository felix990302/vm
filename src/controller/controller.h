#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <deque>
#include "controller/command/motion/direction.h"
#include "model/buffer_type.h"
#include <map>


namespace VM {
    class Input;
    class FileBuffer;
    class Mode;
    class Motion;
    class Command;
    class UndoableCommand;
    class InsertMode;
    class ReplaceMode;
    class CommandMode;
    class ColonCommandMode;
    class BufferView;
    template<Direction dir>class SearchCommandMode;

    class Controller {
        typedef std::deque<std::unique_ptr<UndoableCommand>> CommandStack;

        std::unique_ptr<Input> input; 
        FileBuffer *fileBuffer;
        BufferView *bufferView;


    private:
        CommandStack undoStack;
        CommandStack redoStack;
        std::string message;

        bool programIsRunning;

        struct Modes {
            std::unique_ptr<InsertMode> insertMode;
            std::unique_ptr<ReplaceMode> replaceMode;
            std::unique_ptr<CommandMode> commandMode;
            std::unique_ptr<ColonCommandMode> colonCommandMode;
            std::unique_ptr<SearchCommandMode<Direction::DOWN>> searchDownMode;
            std::unique_ptr<SearchCommandMode<Direction::UP>> searchUpMode;
            
            Modes(Controller &controller);
        };

        struct ClipBoard {
            bool multiLine;
            LineType theClipBoard;
            ClipBoard(bool b=false);
        };


    public:
        Modes modes;
        ClipBoard clipBoard;

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
        void runUndoableCommand(std::unique_ptr<UndoableCommand> command);
        void runSimpleCommand(std::unique_ptr<Command> command);
        void pushCommand(std::unique_ptr<UndoableCommand> &&undoableCommand);

        void quit(bool ignoreChanges);
        operator bool() const {return programIsRunning;}
        BufferView &getBufferView() { return  *bufferView;}
        void setBufferView(BufferView *bufferView1) { bufferView = bufferView1;}

        Controller(std::unique_ptr<Input> input, FileBuffer *fileBuffer, BufferView *bufferView);
        Controller(const Controller &other) = delete;

        const std::string &getMessage() const;

        void setMessage(const std::string &message);

        ~Controller();
    };
}

#endif
