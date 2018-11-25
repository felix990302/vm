#include "insert_command.h"
#include "controller/controller.h"


namespace VM {
    void InsertCommand::doTheCommand(Controller &controller) const {
        controller.getBuffer().type(toMutate);
    }

    void InsertCommand::undoCommand(Controller &controller) const {
        controller.getBuffer().delete_backward(1);
    }
}
