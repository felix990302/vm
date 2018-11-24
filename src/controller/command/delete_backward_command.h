#ifndef DELETE_BACKWARD_COMMAND_H
#define DELETE_BACKWARD_COMMAND_H

#include <string>
#include "mutate_command.h"


namespace VM {
    class DeleteBackwardCommand: public MutateCommand {
        protected:
        void doTheCommand(Controller &controller) const override;
        void sideEffect(Controller &controller) override;

        public:
        void undoCommand(Controller &controller) const override;

        std::unique_ptr<Command> clone() const override;
        DeleteBackwardCommand();
        DeleteBackwardCommand(const DeleteBackwardCommand &other);
        DeleteBackwardCommand(DeleteBackwardCommand &&other);
    };
}

#endif
