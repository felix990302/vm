#ifndef ENTER_INSERT_COMMAND_H
#define ENTER_INSERT_COMMAND_H

#include "command.h"


namespace VM {
    class EnterInsertCommand: public ClonableCommand<Command, EnterInsertCommand> {
        public:
        void doCommand(Controller &controller) override;
    };
}

#endif
