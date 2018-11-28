#ifndef ENTER_COLON_COMMAND_H
#define ENTER_COLON_COMMAND_H

#include "controller/command/command.h"


namespace VM {
    class EnterColonCommand: public ClonableCommand<Command, EnterColonCommand> {
        public:
        void doCommand(Controller &controller) override;
    };
}

#endif
