#ifndef DELETE_COMMAND_H
#define DELETE_COMMAND_H

#include <string>
#include "mutate_command.h"


namespace VM {
    class DeleteCommand: public MutateCommand {
        protected:
        void doTheCommand(Controller &controller) const override;
        void doTheSideEffect(Controller &controllerr) override;
        void undoTheCommand(Controller &controller) const override;

        public:
        std::unique_ptr<Command> clone() const override;
        DeleteCommand(size_t quant);
    };
}

#endif
