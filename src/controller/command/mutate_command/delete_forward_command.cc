#include "delete_forward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteForwardCommand::doTheCommand(Controller &controller) const {

        controller.getBuffer().delete_forward(quant);
    }

    void DeleteForwardCommand::sideEffect(Controller &) {}

    void DeleteForwardCommand::undoCommand(Controller &) const {} // TODO

    std::unique_ptr<Command> DeleteForwardCommand::clone() const {
        return std::make_unique<DeleteForwardCommand>(*this);
    }

    DeleteForwardCommand::DeleteForwardCommand(): MutateCommand{1, '\0'} {}

    DeleteForwardCommand::DeleteForwardCommand(size_t quant) : MutateCommand{quant, '\0'} {}

    DeleteForwardCommand::DeleteForwardCommand(const DeleteForwardCommand &other): MutateCommand{other} {}

    DeleteForwardCommand::DeleteForwardCommand(DeleteForwardCommand &&other): MutateCommand{std::move(other)} {}
}
