#include "delete_backward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteBackwardCommand::doTheCommand(Controller &controller) const {
        controller.getBuffer().delete_forward(1);
    }

    void DeleteBackwardCommand::sideEffect(Controller &) {} // TODO

    void DeleteBackwardCommand::undoCommand(Controller &controller) const {
        controller.getBuffer().type(toMutate);
    }

    std::unique_ptr<Command> DeleteBackwardCommand::clone() const {
        return std::make_unique<DeleteBackwardCommand>(*this);
    }

    DeleteBackwardCommand::DeleteBackwardCommand(): MutateCommand{1, '\0'} {}

    DeleteBackwardCommand::DeleteBackwardCommand(const DeleteBackwardCommand &other): MutateCommand{other} {}

    DeleteBackwardCommand::DeleteBackwardCommand(DeleteBackwardCommand &&other): MutateCommand{std::move(other)} {}
}
