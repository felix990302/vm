#ifndef ENTER_REPLACE_COMMAND_H
#define ENTER_REPLACE_COMMAND_H

#include "controller/command/command.h"


namespace VM {
    class EnterReplaceCommand: public ClonableCommand<Command, EnterReplaceCommand> {
        public:
        void doCommand(Controller &controller) override;

        EnterReplaceCommand(size_t quant): Clonable{quant} {}
        EnterReplaceCommand(const EnterReplaceCommand &other): Clonable{other} {}
        EnterReplaceCommand(EnterReplaceCommand &other): Clonable{std::move(other)} {}
    };
}

#endif
