#include "mode/mode.h"
#include "input.h"
#include "quit_exception.h"
#include "mode/lazy_command_mode/search_command_mode.h"
#include "mode/lazy_command_mode/colon_command_mode.h"
#include "mode/insert_mode.h"
#include "mode/command_mode.h"
#include "controller.h"


namespace VM {
    Controller::Modes::Modes(Controller &controller):
        insertMode{std::make_unique<InsertMode>(controller)},
        commandMode{std::make_unique<CommandMode>(controller)},
        colonCommandMode{std::make_unique<ColonCommandMode>(controller)},
        searchDownMode{std::make_unique<SearchCommandMode<Direction::DOWN>>(controller)},
        searchUpMode{std::make_unique<SearchCommandMode<Direction::UP>>(controller)}
    {}

    Controller::ClipBoard::ClipBoard(bool b):
        shouldPasteInline{b},
        theClipBoard{}
    {}
    
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
        clipBoard{},
        mode{modes.commandMode.get()}
    {}

    void Controller::quit(bool ignoreChanges) {
        if(!undoStack.empty() && !ignoreChanges) {
            throw ProgramQuitException {};
        }
        else {
            programIsRunning = false;
        }
    }

    void Controller::runCommand(std::unique_ptr<Command> command) {
        command->doCommand(*this);

        if(dynamic_cast<UndoableCommand *>(command.get())) {
            undoStack.emplace_front(static_cast<UndoableCommand *>(command.release()));
            redoStack.clear();
        }
    }

    void Controller::runUndoableCommand(std::unique_ptr<UndoableCommand> command) {
        command->doCommand(*this);
        undoStack.push_front(std::move(command));
        redoStack.clear();
    }

    void Controller::runSimpleCommand(std::unique_ptr<Command> command) {
        command->doCommand(*this);
    }

    void Controller::pushCommand(std::unique_ptr<UndoableCommand> &&undoableCommand) {
        undoStack.push_front(std::move(undoableCommand));
        redoStack.clear();
    }

    Controller::~Controller() {}
}
