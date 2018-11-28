#include "delete_backward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteBackwardCommand::doTheCommand(Controller &controller) const {
        controller.getBuffer().delete_backward(quant);
    }

    void DeleteBackwardCommand::sideEffect(Controller &) {} // TODO

    void DeleteBackwardCommand::undoCommand(Controller &) const {} // TODO

    DeleteBackwardCommand::DeleteBackwardCommand(): Clonable{static_cast<size_t>(1), '\0'} {}

    DeleteBackwardCommand::DeleteBackwardCommand(const DeleteBackwardCommand &other): Clonable{other} {}

    DeleteBackwardCommand::DeleteBackwardCommand(size_t quant): Clonable{quant, '\0'} {}

    DeleteBackwardCommand::DeleteBackwardCommand(const DeleteBackwardCommand &other): Clonable{other} {}

    DeleteBackwardCommand::DeleteBackwardCommand(DeleteBackwardCommand &&other): Clonable{std::move(other)} {}
}
