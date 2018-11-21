#ifndef DELETE_COMMAND_H
#define DELETE_COMMAND_H

#include <string>
#include "mutate_command.h"
#include "direction.h"


namespace VM {
    class DeleteCommand: public MutateCommand {
        public:
        void doCommand() override;
        void undoCommand() override;
        void redoCommand() override;

        std::unique_ptr<Command> clone() override;
        DeleteCommand(const size_t &quant, Direction direction, const std::string &toDelete);
    };
}

#endif
