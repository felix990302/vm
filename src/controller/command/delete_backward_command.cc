#include "delete_backward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteBackwardCommand::doTheCommand(Controller &controller) const {
        controller.getBuffer()->delete_forward(toMutate.size());
    }

    void DeleteBackwardCommand::sideEffect(Controller &controller) {
        toMutate = *(controller.getBuffer()->ptrCursor.charPosn);
    }

    void DeleteBackwardCommand::undoCommand(Controller &controller) const {
        controller.getBuffer()->type(toMutate);
    }

    std::unique_ptr<Command> DeleteBackwardCommand::clone() const {
        return std::make_unique<DeleteBackwardCommand>(*this);
    }

    DeleteBackwardCommand::DeleteBackwardCommand(size_t quant): MutateCommand{quant, ""} {}

    DeleteBackwardCommand::DeleteBackwardCommand(const DeleteBackwardCommand &other): MutateCommand{other} {}

    DeleteBackwardCommand::DeleteBackwardCommand(DeleteBackwardCommand &&other): MutateCommand{std::move(other)} {}
}
