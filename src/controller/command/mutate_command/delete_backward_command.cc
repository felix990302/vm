#include "delete_backward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    inline void DeleteBackwardCommand::commandHelper(Controller &controller) const {
        controller.getBuffer().delete_backward(quant);
    }

    void DeleteBackwardCommand::doTheCommand(Controller &controller) {
        toMutate = *controller.getBuffer().ptrCursor;
        commandHelper(controller);
    }

    void DeleteBackwardCommand::undoTheCommand(Controller &controller) const {
        controller.getBuffer().type(toMutate);
    }

    void DeleteBackwardCommand::redoTheCommand(Controller &controller) const {
        commandHelper(controller);
    }

    DeleteBackwardCommand::DeleteBackwardCommand(const DeleteBackwardCommand &other): Clonable{other} {}

    DeleteBackwardCommand::DeleteBackwardCommand(size_t quant): Clonable{quant, '\0'} {}

    DeleteBackwardCommand::DeleteBackwardCommand(DeleteBackwardCommand &&other): Clonable{std::move(other)} {}
}
