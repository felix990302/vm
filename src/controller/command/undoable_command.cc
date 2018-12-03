#include "controller/controller.h"
#include "model/ptr_cursor.h"
#include "model/file_buffer.h"
#include "undoable_command.h"


namespace VM {
    void UndoableCommand::doCommand(Controller & controller) {
        startPosn = controller.getBuffer().ptrCursor;
        doTheCommand(controller);
        endPosn = controller.getBuffer().ptrCursor;
    }
    void UndoableCommand::undoCommand(Controller &controller) const {
        controller.getBuffer().ptrCursor.setCursor(endPosn);
        undoTheCommand(controller);
        controller.getBuffer().ptrCursor.setCursor(startPosn); //TODO check
    }
    void UndoableCommand::redoCommand(Controller &controller) const {
        controller.getBuffer().ptrCursor.setCursor(startPosn);
        redoTheCommand(controller);
    }

    // FIXME: find another non-sketchy way to clone
    std::unique_ptr<UndoableCommand> UndoableCommand::undoableclone() const {
        return std::unique_ptr<UndoableCommand>(
                static_cast<UndoableCommand*>(clone().release())
        );
    };

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
