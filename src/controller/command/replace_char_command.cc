#include "model/ptr_cursor.h"
#include "controller/controller.h"
#include "replace_char_command.h"


namespace VM {
    inline void ReplaceCharCommand::commandHelper(Controller &controller) const {
        controller.getBuffer().delete_forward(1);
        controller.getBuffer().type(inserted);
        controller.getBuffer().ptrCursor.moveLeft();
    }

    void ReplaceCharCommand::doTheCommand(Controller &controller) {
        deleted = *controller.getBuffer().ptrCursor;
        commandHelper(controller);
    }

    void ReplaceCharCommand::undoTheCommand(Controller &controller) const {
        controller.getBuffer().delete_forward(1);
        controller.getBuffer().type(deleted);
        controller.getBuffer().ptrCursor.moveLeft();
    }

    void ReplaceCharCommand::redoTheCommand(Controller &controller) const {
        commandHelper(controller);
    }
}
