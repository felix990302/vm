#ifndef INSERT_COMMAND_H
#define INSERT_COMMAND_H

#include "mutate_command.h"


namespace VM {
    class InsertCommand: public MutateCommand {
        protected:
        void doTheCommand(Controller &controller) const override;

        public:
        void undoCommand(Controller &controlle) const override;

        std::unique_ptr<Command> clone() const override;
        InsertCommand(size_t quant, char c);
        InsertCommand(const InsertCommand &other);
        InsertCommand(InsertCommand &&other);
    };
}

#endif
