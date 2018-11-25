#include "mutate_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void MutateCommand::doCommand(Controller &controller) {
        startPosn = controller.getBuffer().ptrCursor;
        sideEffect(controller);
        doTheCommand(controller);
        endPosn = controller.getBuffer().ptrCursor;
    }

    void MutateCommand::redoCommand(Controller &controller) const {
        doTheCommand(controller);
    }

    MutateCommand::MutateCommand(size_t quant, char c):
        UndoableCommand{quant},
        toMutate{c}
    {}

    MutateCommand::MutateCommand(const MutateCommand &other): UndoableCommand{other}, toMutate{other.toMutate} {}

    MutateCommand::MutateCommand(MutateCommand &&other): UndoableCommand{std::move(other)}, toMutate{std::move(other.toMutate)} {}

    MutateCommand::~MutateCommand() {}
}
