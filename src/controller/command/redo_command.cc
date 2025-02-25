#include "undoable_command.h"
#include "controller/controller.h"
#include "redo_command.h"


namespace VM {
    void RedoCommand::doCommand(Controller &controller) {
        for(size_t k=0; k<quant; ++k) {
            if(!controller.getRedoStack().empty()) {
                controller.getRedoStack().front()->redoCommand(controller); 
                controller.getUndoStack().emplace_front(
                        controller.getRedoStack().front().release()
                );
                controller.getRedoStack().pop_front();
            }
        }
    }

    RedoCommand::RedoCommand(size_t quant): Clonable{quant} {}

    RedoCommand::RedoCommand(const RedoCommand &other): Clonable{other} {}

    RedoCommand::RedoCommand(RedoCommand &&other): Clonable{std::move(other)} {}

    RedoCommand::~RedoCommand() {}
}
