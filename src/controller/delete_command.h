#ifndef DELETE_COMMAND_H
#define DELETE_COMMAND_H

#include <string>
#include "mutate_command.h"
#include "direction.h"


namespace VM {
    class DeleteCommand: public MutateCommand {
        protected:
        void doTheCommand() override;
        void undoTheCommand() override;

        public:
        std::unique_ptr<Command> clone() const override;
        DeleteCommand(const size_t &quant, Direction direction, const std::string &toDelete);
    };
}

#endif
