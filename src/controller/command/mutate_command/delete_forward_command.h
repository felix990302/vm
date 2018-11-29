#ifndef DELETE_FORWARD_COMMAND_H
#define DELETE_FORWARD_COMMAND_H

#include <string>
#include "mutate_command.h"


namespace VM {
    class DeleteForwardCommand: public ClonableCommand<MutateCommand, DeleteForwardCommand> {
        void commandHelper(Controller &controller) const;
        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &controller) const override;
        void redoTheCommand(Controller &controller) const override;

        public:
        DeleteForwardCommand();
        DeleteForwardCommand(size_t quant);
        DeleteForwardCommand(const DeleteForwardCommand &other);
        DeleteForwardCommand(DeleteForwardCommand &&other);
    };
}

#endif
