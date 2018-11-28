#include "mode/mode.h"
#include "input.h"
#include "quit_exception.h"
#include "controller.h"


namespace VM {
    void Controller::getAndProcessChar() {
        mode->processChar(input->getChar());
    }

    Controller::Controller(std::unique_ptr<Input> input, FileBuffer *fileBuffer):
        input{std::move(input)},
        fileBuffer{fileBuffer},
        undoStack{},
        redoStack{},
        programIsRunning{true},
        modes{*this},
        mode{&modes.commandMode}
    {}

    void Controller::quit(bool ignoreChanges) {
        if(!redoStack.empty() && !ignoreChanges) {
            throw ProgramQuitException {};
        }
        else {
            programIsRunning = false;
        }
    }

    void Controller::runCommand(std::unique_ptr<Command> command) {
        command->doCommand(*this);

        if(dynamic_cast<UndoableCommand *>(command.get())) {
            undoStack.emplace(static_cast<UndoableCommand *>(command.release()));
        }
    }

    void Controller::pushCommand(std::unique_ptr<UndoableCommand> undoableCommand) {
        undoStack.push(std::move(undoableCommand));
    }
}
