#include "insert_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void InsertCommand::doTheCommand(Controller &controller) const {
        controller.getBuffer()->type(toMutate);
    }

    void InsertCommand::undoCommand(Controller &controller) const {
        controller.getBuffer()->delete_backward(1);
    }

    std::unique_ptr<Command> InsertCommand::clone() const {
        return std::make_unique<InsertCommand>(*this);
    }

    InsertCommand::InsertCommand(size_t quant, char c):
        MutateCommand{quant, c}
    {}

    InsertCommand::InsertCommand(const InsertCommand &other): MutateCommand{other} {}

    InsertCommand::InsertCommand(InsertCommand &&other): MutateCommand{std::move(other)} {}
}
