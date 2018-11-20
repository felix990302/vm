#ifndef INSERT_COMMAND_H
#define INSERT_COMMAND_H

#include <string>
#include "command.h"
#include "direction.h"


namespace VM {
    class InsertCommand: public Command {
        const Direction direction;
        std::string toInsert;

        public:
        void doCommand() override;
        std::unique_ptr<Command> clone() override;

        InsertCommand(const size_t &quant, Direction direction, const std::string &toInsert);
    };
}

#endif
