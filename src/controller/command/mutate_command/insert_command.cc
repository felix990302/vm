#include "controller/controller.h"
#include "insert_command.h"
#include "controller/controller.h"


namespace VM {
    inline void InsertCommand::commandHelper(Controller &controller) const {
        for(size_t k=0; k<quant; ++k) controller.getBuffer().type(toMutate);
    }

    void InsertCommand::doTheCommand(Controller &controller) {
        commandHelper(controller);
    }

    void InsertCommand::undoTheCommand(Controller &controller) const {
        for(size_t k=0; k<quant; ++k) controller.getBuffer().delete_backward(quant);
    }

    void InsertCommand::redoTheCommand(Controller &controller) const {
        commandHelper(controller);
    }
}
