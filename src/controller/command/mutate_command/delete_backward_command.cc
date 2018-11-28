#include "delete_backward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteBackwardCommand::doTheCommand(Controller &controller) const {
        controller.getBuffer().delete_backward(quant);
    }

    void DeleteBackwardCommand::sideEffect(Controller &) {} // TODO

    void DeleteBackwardCommand::undoCommand(Controller &) const {} // TODO

    std::unique_ptr<Command> DeleteBackwardCommand::clone() const {
        return std::make_unique<DeleteBackwardCommand>(*this);
    }

    DeleteBackwardCommand::DeleteBackwardCommand(): MutateCommand{1, '\0'} {}

    DeleteBackwardCommand::DeleteBackwardCommand(size_t quant): MutateCommand{quant, '\0'} {}

    DeleteBackwardCommand::DeleteBackwardCommand(const DeleteBackwardCommand &other): MutateCommand{other} {}

    DeleteBackwardCommand::DeleteBackwardCommand(DeleteBackwardCommand &&other): MutateCommand{std::move(other)} {}
}
