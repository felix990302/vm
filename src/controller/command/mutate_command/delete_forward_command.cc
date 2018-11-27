#include "delete_forward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteForwardCommand::doTheCommand(Controller &controller) const {
        controller.getBuffer().delete_forward(quant);
    }

    void DeleteForwardCommand::sideEffect(Controller &) {}

    void DeleteForwardCommand::undoCommand(Controller &) const {} // TODO

    DeleteForwardCommand::DeleteForwardCommand(): ClonableCommand{static_cast<size_t>(1), '\0'} {}

    DeleteForwardCommand::DeleteForwardCommand(const DeleteForwardCommand &other): ClonableCommand{other} {}

    DeleteForwardCommand::DeleteForwardCommand(DeleteForwardCommand &&other): ClonableCommand{std::move(other)} {}
}
