#ifndef INSERT_COMMAND_H
#define INSERT_COMMAND_H

#include "mutate_command.h"
#include "model/file_buffer.h"


namespace VM {
    class InsertCommand: public ClonableCommand<MutateCommand, InsertCommand> {
        protected:
        void doTheCommand(Controller &controller) const override;

        public:
        void undoCommand(Controller &controller) const override;

        InsertCommand(size_t quant, char c): Clonable{quant, c} {}
        InsertCommand(const InsertCommand &other): Clonable{other} {}
        InsertCommand(InsertCommand &&other): Clonable{std::move(other)} {}
    };
}

#endif
