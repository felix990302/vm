#include "undoable_command.h"


namespace VM {
    void UndoableCommand::undoCommand() {
        undoTheCommand();
    }

    void UndoableCommand::redoCommand() {
        doTheCommand(); 
    }

    UndoableCommand::UndoableCommand(const size_t &quant): Command{quant} {} 

    UndoableCommand::~UndoableCommand() {}
}
