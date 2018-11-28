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
        mode{modes.commandMode.get()}
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

    Controller::~Controller() {}
}
