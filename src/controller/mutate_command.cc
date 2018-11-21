#include "mutate_command.h"


namespace VM {
    MutateCommand::MutateCommand(const size_t &quant, Direction direction, const std::string &toMutate):
        UndoableCommand{quant},
        direction{direction},
        toMutate{toMutate}
    {}

    MutateCommand::~MutateCommand() {}
}
