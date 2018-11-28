#ifndef DELETE_BACKWARD_COMMAND_H
#define DELETE_BACKWARD_COMMAND_H

#include <string>
#include "mutate_command.h"


namespace VM {
    class DeleteBackwardCommand: public ClonableCommand<MutateCommand, DeleteBackwardCommand> {
        protected:
        void doTheCommand(Controller &controller) const override;
        void sideEffect(Controller &controller) override;

        public:
        void undoCommand(Controller &controller) const override;

        DeleteBackwardCommand();
        DeleteBackwardCommand(size_t quant);
        DeleteBackwardCommand(const DeleteBackwardCommand &other);
        DeleteBackwardCommand(DeleteBackwardCommand &&other);
    };
}

#endif
