#include <typeinfo>
#include "mode/mode.h"
#include "input.h"
#include "quit_exception.h"
#include "mode/lazy_command_mode/search_command_mode.h"
#include "mode/lazy_command_mode/colon_command_mode.h"
#include "mode/insert_mode.h"
#include "mode/replace_mode.h"
#include "mode/command_mode.h"
#include "controller/command/macro/toggle_record_macro_command.h"
#include "controller.h"


namespace VM {
    Controller::Modes::Modes(Controller &controller):
        insertMode{std::make_unique<InsertMode>(controller)},
        replaceMode{std::make_unique<ReplaceMode>(controller)},
        commandMode{std::make_unique<CommandMode>(controller)},
        colonCommandMode{std::make_unique<ColonCommandMode>(controller)},
        searchDownMode{std::make_unique<SearchCommandMode<Direction::DOWN>>(controller)},
        searchUpMode{std::make_unique<SearchCommandMode<Direction::UP>>(controller)}
    {}

    Controller::ClipBoard::ClipBoard(bool b):
        multiLine{b},
        theClipBoard{}
    {}
    
    void Controller::getAndProcessChar() {
        mode->processChar(input->getChar());
    }

    Controller::Controller(std::unique_ptr<Input> input, FileBuffer *fileBuffer, BufferView *bufferView):
        input{std::move(input)},
        fileBuffer{fileBuffer},
        bufferView {bufferView},
        undoStack{},
        redoStack{},
        macroRecKey{0},
        macroMap{},
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
        runSimpleCommand(command.get());

        if(dynamic_cast<UndoableCommand *>(command.get())) {
            undoStack.emplace_front(static_cast<UndoableCommand *>(command.release()));
            redoStack.clear();
        }
    }

    void Controller::runUndoableCommand(std::unique_ptr<UndoableCommand> command) {
        runSimpleCommand(command.get());
        undoStack.push_front(std::move(command));
        redoStack.clear();
    }

    void Controller::recordIfToggledCommand(Command* command) {
        if(macroRecKey && typeid(*command)!=typeid(ToggleRecordMacroCommand)) {
            macroMap[macroRecKey].push_back(command->clone());
        }
    }

    void Controller::runSimpleCommand(Command* command) {
        recordIfToggledCommand(command);
        command->doCommand(*this);
    }

    void Controller::pushCommand(std::unique_ptr<UndoableCommand> &&undoableCommand) {
        recordIfToggledCommand(undoableCommand.get());
        undoStack.push_front(std::move(undoableCommand));
        redoStack.clear();
    }

    Controller::~Controller() {}
}
