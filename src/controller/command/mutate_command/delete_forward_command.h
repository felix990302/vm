#ifndef DELETE_FORWARD_COMMAND_H
#define DELETE_FORWARD_COMMAND_H

#include <string>
#include "mutate_command.h"


namespace VM {
    class DeleteForwardCommand: public ClonableCommand<MutateCommand, DeleteForwardCommand> {
        protected:
        void doTheCommand(Controller &controller) const override;
        void sideEffect(Controller &controller) override;

        public:
        void undoCommand(Controller &controller) const override;

        std::unique_ptr<Command> clone() const override;
        DeleteForwardCommand();
        DeleteForwardCommand(size_t quant);
        DeleteForwardCommand(const DeleteForwardCommand &other);
        DeleteForwardCommand(DeleteForwardCommand &&other);
    };
}

#endif
