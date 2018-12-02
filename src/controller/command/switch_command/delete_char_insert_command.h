#ifndef DELETE_CHAR_INSERT_COMMAND
#define DELETE_CHAR_INSERT_COMMAND

#include "controller/command/command.h"


namespace VM {
    class DeleteCharInsertCommand: public ClonableCommand<Command, DeleteCharInsertCommand> {
        public:
        void doCommand(Controller &controller) override;

        DeleteCharInsertCommand(size_t quant): Clonable{quant} {}
        DeleteCharInsertCommand(const DeleteCharInsertCommand &other): Clonable{other} {}
        DeleteCharInsertCommand(DeleteCharInsertCommand &&other): Clonable{std::move(other)} {}
    };
}

#endif
