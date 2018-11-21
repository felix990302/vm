#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <memory>
#include "command.h"
#include "motion.h"


namespace VM {
    class MoveCommand: public Command {
        std::unique_ptr<Motion> motion;

        protected:
        void doTheCommand(FileBuffer &fileBuffer) const override;

        public:
        std::unique_ptr<Command> clone() const override;

        MoveCommand(std::unique_ptr<Motion> motion, const size_t &quant=1);
        MoveCommand(const Command &other);
        MoveCommand(const Command &&other);
        MoveCommand &operator=(Command other);
    };
}

#endif
