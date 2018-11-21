#include "undoable_command.h"


namespace VM {
    UndoableCommand::UndoableCommand(const size_t &quant): Command{quant} {} 

    UndoableCommand::~UndoableCommand() {}
}
