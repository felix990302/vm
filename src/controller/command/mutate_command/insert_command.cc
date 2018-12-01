#include "controller/controller.h"
#include "insert_command.h"
#include "controller/controller.h"


namespace VM {
    inline void InsertCommand::commandHelper(Controller &controller) const {
        controller.getBuffer().type(toMutate);
    }

    void InsertCommand::doTheCommand(Controller &controller) {
        commandHelper(controller);
    }

    void InsertCommand::undoTheCommand(Controller &controller) const {
        controller.getBuffer().delete_backward(1);
    }

    void InsertCommand::redoTheCommand(Controller &controller) const {
        commandHelper(controller);
    }
}
