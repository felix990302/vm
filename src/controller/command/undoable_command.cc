#include "undoable_command.h"


namespace VM {
    const Cursor &UndoableCommand::getCursor() {return cursor;}

    void UndoableCommand::setCursor(const Cursor &newCursor) {
        cursor = newCursor;
    }

    void UndoableCommand::undoCommand(Controller &controller) {
        undoTheCommand(controller);
    }

    void UndoableCommand::redoCommand(Controller &controller) {
        doTheCommand(controller); 
    }

    UndoableCommand::UndoableCommand(size_t quant): Command{quant} {} 

    UndoableCommand::UndoableCommand(const UndoableCommand &other): Command{other}, cursor{other.cursor} {} 

    UndoableCommand::UndoableCommand(UndoableCommand &&other): Command{std::move(other)}, cursor{std::move(other.cursor)} {} 

    UndoableCommand::~UndoableCommand() {}
}
