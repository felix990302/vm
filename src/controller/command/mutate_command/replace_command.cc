#include "model/ptr_cursor.h"
#include "controller/controller.h"
#include "replace_command.h"


namespace VM {
    inline void ReplaceCommand::commandHelper(Controller &controller) const {
        controller.getBuffer().delete_forward(1);
        controller.getBuffer().type(toMutate);
        controller.getBuffer().ptrCursor.moveLeft();
    }

    void ReplaceCommand::doTheCommand(Controller &controller) {
        deleted = *controller.getBuffer().ptrCursor;
        commandHelper(controller);
    }

    void ReplaceCommand::undoTheCommand(Controller &controller) const {
        controller.getBuffer().delete_forward(1);
        controller.getBuffer().type(deleted);
        controller.getBuffer().ptrCursor.moveLeft();
    }

    void ReplaceCommand::redoTheCommand(Controller &controller) const {
        commandHelper(controller);
    }
}
