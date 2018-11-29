#include "undoable_command.h"
#include "controller/controller.h"
#include "undo_command.h"


namespace VM {
    void UndoCommand::doCommand(Controller &controller) {
        for(size_t k=0; k<quant; ++k) {
            if(!controller.getUndoStack().empty()) {
                controller.getUndoStack().front()->undoCommand(controller);
                controller.getRedoStack().emplace_front(
                        controller.getUndoStack().front().release()
                );
                controller.getUndoStack().pop_front();
            }
        }
    }

    UndoCommand::UndoCommand(size_t quant): Clonable{quant} {}

    UndoCommand::UndoCommand(const UndoCommand &other): Clonable{other} {}

    UndoCommand::UndoCommand(UndoCommand &&other): Clonable{std::move(other)} {}
}
