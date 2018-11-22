#include "mutate_command.h"


namespace VM {
    MutateCommand::MutateCommand(size_t quant, const std::string &toMutate):
        UndoableCommand{quant},
        toMutate{toMutate}
    {}

    MutateCommand::MutateCommand(size_t quant, char c):
        UndoableCommand{quant},
        toMutate{c}
    {}

    MutateCommand::MutateCommand(const MutateCommand &other): UndoableCommand{other}, toMutate{other.toMutate} {}

    MutateCommand::MutateCommand(MutateCommand &&other): UndoableCommand{std::move(other)}, toMutate{std::move(other.toMutate)} {}

    MutateCommand::~MutateCommand() {}
}
