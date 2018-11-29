#include "controller/controller.h"
#include "dot_command.h"


namespace VM {
    void DotCommand::doCommand(Controller &controller) {
        for(size_t k=0; k<quant; ++k)
            controller.runCommand(controller.getRedoStack().front()->undoableclone());
    }

    DotCommand::DotCommand(size_t quant): Clonable{quant} {}

    DotCommand::DotCommand(const DotCommand &other): Clonable{other} {}

    DotCommand::DotCommand(DotCommand &&other): Clonable{std::move(other)} {}
}
