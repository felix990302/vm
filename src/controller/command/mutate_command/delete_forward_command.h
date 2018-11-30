#ifndef DELETE_FORWARD_COMMAND_H
#define DELETE_FORWARD_COMMAND_H

#include "mutate_command.h"


namespace VM {
    class DeleteForwardCommand: public ClonableCommand<MutateCommand, DeleteForwardCommand> {
        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &controller) const override;
        void redoTheCommand(Controller &controller) const override;

        public:
        DeleteForwardCommand(size_t quant=1);
        DeleteForwardCommand(const DeleteForwardCommand &other);
        DeleteForwardCommand(DeleteForwardCommand &&other);
    };
}

#endif
