#include "controller/controller.h"
#include "controller/controller.h"
#include "model/file_buffer.h"
#include "replace_command.h"


namespace VM {
    inline void ReplaceCommand::commandHelper(Controller &controller) const {
        if(deleted) controller.getBuffer().delete_forward(1);
        controller.getBuffer().type(toMutate);
    }

    void ReplaceCommand::doTheCommand(Controller &controller) {
        if(!controller.getBuffer().ptrCursor.isEOL())
            deleted = *controller.getBuffer().ptrCursor;
        commandHelper(controller);
    }

    void ReplaceCommand::undoTheCommand(Controller &controller) const {
        controller.getBuffer().delete_backward(1);
        if(deleted) controller.getBuffer().type(deleted);
    }

    void ReplaceCommand::redoTheCommand(Controller &controller) const {
        commandHelper(controller);
    }
}
