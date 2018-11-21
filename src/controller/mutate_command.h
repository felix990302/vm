#ifndef MUTATE_COMMAND_H
#define MUTATE_COMMAND_H

#include <string>
#include "undoable_command.h"
#include "direction.h"


namespace VM {
    class MutateCommand: public UndoableCommand {
        const Direction direction;
        std::string toMutate;

        public:
        MutateCommand(const size_t &quant, Direction direction, const std::string &toMutate);

        virtual ~MutateCommand();
    };
}

#endif
