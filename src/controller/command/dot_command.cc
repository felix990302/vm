#include "controller/command/undoable_command.h"
#include "controller/controller.h"
#include "dot_command.h"


namespace VM {
    void DotCommand::doCommand(Controller &controller) {
        if(!controller.getUndoStack().empty()) {
            std::unique_ptr<UndoableCommand> toRepeat = controller.getUndoStack().front()->undoableclone();
            if(quant > 1) toRepeat->setQuant(quant);
            controller.runUndoableCommand(std::move(toRepeat));
        }
    }

    DotCommand::DotCommand(size_t quant): Clonable{quant} {}

    DotCommand::DotCommand(const DotCommand &other): Clonable{other} {}

    DotCommand::DotCommand(DotCommand &&other): Clonable{std::move(other)} {}
}
