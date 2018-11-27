#include "delete_backward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteBackwardCommand::doTheCommand(Controller &controller) const {
        controller.getBuffer().delete_backward(quant);
    }

    void DeleteBackwardCommand::sideEffect(Controller &) {} // TODO

    void DeleteBackwardCommand::undoCommand(Controller &) const {} // TODO

    DeleteBackwardCommand::DeleteBackwardCommand(): ClonableCommand{static_cast<size_t>(1), '\0'} {}

    DeleteBackwardCommand::DeleteBackwardCommand(const DeleteBackwardCommand &other): ClonableCommand{other} {}

    DeleteBackwardCommand::DeleteBackwardCommand(DeleteBackwardCommand &&other): ClonableCommand{std::move(other)} {}
}
