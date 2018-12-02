#ifndef ENTER_INSERT_COMMAND_H
#define ENTER_INSERT_COMMAND_H

#include "controller/command/command.h"


namespace VM {
    class EnterInsertCommand: public ClonableCommand<Command, EnterInsertCommand> {
        public:
        void doCommand(Controller &controller) override;

        EnterInsertCommand(size_t quant): Clonable{quant} {}
        EnterInsertCommand(const EnterInsertCommand &other): Clonable{other} {}
        EnterInsertCommand(EnterInsertCommand &&other): Clonable{std::move(other)} {}
    };
}

#endif
