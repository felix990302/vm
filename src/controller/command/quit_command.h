#ifndef QUIT_COMMAND_H
#define QUIT_COMMAND_H

#include "command.h"


namespace VM {
    class QuitCommand: public ClonableCommand<Command, QuitCommand> {
        bool shouldForce;
        
        void doCommand(Controller &controller) override;

        public:
        QuitCommand(bool b): shouldForce{b} {}
    };
}

#endif
