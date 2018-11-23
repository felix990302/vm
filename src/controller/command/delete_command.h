#ifndef DELETE_COMMAND_H
#define DELETE_COMMAND_H

#include <string>
#include "mutate_command.h"


namespace VM {
    class DeleteForwardCommand: public MutateCommand {
        protected:
        void doTheCommand(Controller &controller) const override;

        public:
        void undoCommand(Controller &controller) const override;

        std::unique_ptr<Command> clone() const override;
        DeleteForwardCommand(size_t quant);
        DeleteForwardCommand(const DeleteForwardCommand &other);
        DeleteForwardCommand(DeleteForwardCommand &&other);
    };
}

#endif
