#ifndef MUTATE_COMMAND_H
#define MUTATE_COMMAND_H

#include <string>
#include "model/cursor.h"
#include "controller/command/undoable_command.h"


namespace VM {
    class MutateCommand: public UndoableCommand {
        protected:
        std::string toMutate;

        public:
        MutateCommand(size_t quant, char c);
        MutateCommand(const MutateCommand &other);
        MutateCommand(MutateCommand &&other);
        virtual ~MutateCommand();
    };
}

#endif
