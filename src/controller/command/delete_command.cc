#include "delete_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteForwardCommand::doTheCommand(Controller &controller) const {
        controller.getBuffer()->delete_forward(toMutate.size());
    }

    void DeleteForwardCommand::undoCommand(Controller &controller) const {
        controller.getBuffer()->type(toMutate);
    }

    std::unique_ptr<Command> DeleteForwardCommand::clone() const {
        return std::make_unique<DeleteForwardCommand>(*this);
    }

    DeleteForwardCommand::DeleteForwardCommand(size_t quant): MutateCommand{quant, ""} {}

    DeleteForwardCommand::DeleteForwardCommand(const DeleteForwardCommand &other): MutateCommand{other} {}

    DeleteForwardCommand::DeleteForwardCommand(DeleteForwardCommand &&other): MutateCommand{std::move(other)} {}
}
