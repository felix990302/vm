#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <memory>
#include "command.h"
#include "motion.h"


namespace VM {
    class MoveCommand: public Command {
        std::unique_ptr<Motion> motion;

        protected:
        void doTheCommand(Controller &controller) const override;

        public:
        std::unique_ptr<Command> clone() const override;

        MoveCommand(size_t quant, std::unique_ptr<Motion> motion);
        MoveCommand(const Command &other);
        MoveCommand(Command &&other);
    };
}

#endif
