#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <memory>
#include "command.h"


namespace VM {
    class Motion;

    class MoveCommand: public ClonableCommand<Command, MoveCommand> {
        protected:
        std::unique_ptr<Motion> motion;

        public:
        void doCommand(Controller &controller) override;

        MoveCommand(size_t quant, std::unique_ptr<Motion> motion);
        MoveCommand(const MoveCommand &other);
        MoveCommand(MoveCommand &&other);
    };
}

#endif
