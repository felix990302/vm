#ifndef QUIT_COMMAND_H
#define QUIT_COMMAND_H

#include "command.h"


namespace VM {
    class QuitCommand: public Command {
        bool shouldForce;
        
        void doCommand(Controller &controller) override;

        public:
        std::unique_ptr<Command> clone() const override;
        QuitCommand(bool b): shouldForce{b} {}
    };
}

#endif
