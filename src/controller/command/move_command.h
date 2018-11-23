#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <memory>
#include "command.h"


namespace VM {
    class Motion;

    class MoveCommand: public Command {
        std::unique_ptr<Motion> motion;

        protected:
        void doTheCommand(Controller &controller) const override;
        void doTheSideEffect(Controller &controller) override {}

        public:
        std::unique_ptr<Command> clone() const override;

        MoveCommand(size_t quant, std::unique_ptr<Motion> motion);
        MoveCommand(const MoveCommand &other);
        MoveCommand(MoveCommand &&other);
    };
}

#endif
