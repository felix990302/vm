#include "insert_command.h"
#include "controller/controller.h"


namespace VM {
    void InsertCommand::doTheCommand(Controller &controller) const {
        for(size_t k=0; k<quant; ++k) controller.getBuffer().type(toMutate);
    }

    void InsertCommand::undoCommand(Controller &controller) const {
        controller.getBuffer().delete_backward(quant);
    }
}
