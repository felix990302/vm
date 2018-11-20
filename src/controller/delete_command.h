#ifndef DELETE_COMMAND_H
#define DELETE_COMMAND_H

#include <string>
#include "command.h"
#include "direction.h"


namespace VM {
    class DeleteCommand: public Command {
        const Direction direction;
        std::string toDelete;

        public:
        void doCommand() override;
        std::unique_ptr<Command> clone() override;

        DeleteCommand(const size_t &quant, Direction direction, const std::string &toDelete);
    };
}

#endif
