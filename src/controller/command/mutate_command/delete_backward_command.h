#ifndef DELETE_BACKWARD_COMMAND_H
#define DELETE_BACKWARD_COMMAND_H

#include <string>
#include "mutate_command.h"


namespace VM {
    class DeleteBackwardCommand: public ClonableCommand<MutateCommand, DeleteBackwardCommand> {
        void commandHelper(Controller &controller) const;
        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &controller) const override;
        void redoTheCommand(Controller &controller) const override;

        public:

        DeleteBackwardCommand(size_t quant=1);
        DeleteBackwardCommand(const DeleteBackwardCommand &other);
        DeleteBackwardCommand(DeleteBackwardCommand &&other);
    };
}

#endif
