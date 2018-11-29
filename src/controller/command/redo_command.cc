#include "controller/controller.h"
#include "redo_command.h"


namespace VM {
    void RedoCommand::doCommand(Controller &controller) {
        if(!controller.getRedoStack().empty()) {
            controller.getRedoStack().top()->redoCommand(controller); 
            controller.getUndoStack().emplace(
                    controller.getRedoStack().top().release()
            );
            controller.getRedoStack().pop();
        }
    }

    RedoCommand::RedoCommand(size_t quant): Clonable{quant} {}

    RedoCommand::RedoCommand(const RedoCommand &other): Clonable{other} {}

    RedoCommand::RedoCommand(RedoCommand &&other): Clonable{std::move(other)} {}
}
