#include "delete_forward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    inline void DeleteForwardCommand::commandHelper(Controller &controller) const {
        controller.getBuffer().delete_forward(quant);
    }

    void DeleteForwardCommand::doTheCommand(Controller &controller) {
        toMutate = *controller.getBuffer().ptrCursor;
        commandHelper(controller);
    }

    void DeleteForwardCommand::undoTheCommand(Controller &controller) const {
        controller.getBuffer().type(toMutate);
        --controller.getBuffer().ptrCursor;
    }

    void DeleteForwardCommand::redoTheCommand(Controller &controller) const {
        commandHelper(controller);
    }

    DeleteForwardCommand::DeleteForwardCommand(): Clonable{static_cast<size_t>(1), '\0'} {}

    DeleteForwardCommand::DeleteForwardCommand(DeleteForwardCommand &&other): Clonable{std::move(other)} {}

    DeleteForwardCommand::DeleteForwardCommand(size_t quant) : Clonable{quant, '\0'} {}

    DeleteForwardCommand::DeleteForwardCommand(const DeleteForwardCommand &other): Clonable{other} {}
}
