#ifndef DELETE_COMMAND_H
#define DELETE_COMMAND_H

#include <string>
#include "mutate_command.h"


namespace VM {
    class DeleteForwardCommand: public MutateCommand {
        protected:
        void doTheCommand(Controller &controller) const override;
        void doTheSideEffect(Controller &controllerr) override;
        void undoTheCommand(Controller &controller) const override;

        public:
        std::unique_ptr<Command> clone() const override;
        DeleteForwardCommand(size_t quant);
        DeleteForwardCommand(const DeleteForwardCommand &other);
        DeleteForwardCommand(DeleteForwardCommand &&other);
    };
}

#endif
