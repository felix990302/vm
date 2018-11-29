#ifndef DOT_COMMAND_H
#define DOT_COMMAND_H

#include "command.h"


namespace VM {
    class DotCommand: public ClonableCommand<Command, DotCommand> {
        public:
        void doCommand(Controller &controller) override;

        DotCommand(size_t quant);
        DotCommand(const DotCommand &other);
        DotCommand(DotCommand &&other);
    };

}

#endif
