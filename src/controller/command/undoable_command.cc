#include "undoable_command.h"


namespace VM {
    UndoableCommand::UndoableCommand(size_t quant, Cursor startPosn, Cursor endPosn):
        Command{quant},
        startPosn{startPosn},
        endPosn{endPosn}
    {} 

    UndoableCommand::UndoableCommand(const UndoableCommand &other):
        Command{other},
        startPosn{other.startPosn},
        endPosn{other.endPosn}
    {} 

    UndoableCommand::UndoableCommand(UndoableCommand &&other):
        Command{std::move(other)},
        startPosn{std::move(other.startPosn)},
        endPosn{std::move(other.endPosn)}
    {} 

    UndoableCommand::~UndoableCommand() {}
}
