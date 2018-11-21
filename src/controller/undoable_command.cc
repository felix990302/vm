#include "undoable_command.h"


namespace VM {
    void UndoableCommand::undoCommand(FileBuffer &fileBuffer) {
        undoTheCommand(fileBuffer);
    }

    void UndoableCommand::redoCommand(FileBuffer &fileBuffer) {
        doTheCommand(fileBuffer); 
    }

    UndoableCommand::UndoableCommand(const size_t &quant): Command{quant} {} 

    UndoableCommand::~UndoableCommand() {}
}
