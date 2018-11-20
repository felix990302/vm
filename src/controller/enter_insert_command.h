#ifndef ENTER_INSERT_COMMAND_H
#define ENTER_INSERT_COMMAND_H

#include "command.h"


namespace VM {
    class EnterInsertCommand: public Command {
        public:
        void doCommand() override;
        std::unique_ptr<Command> clone() override;

        EnterInsertCommand(const size_t &quant);
    };
}

#endif
