#ifndef DELETE_LINE_INSERT_COMMAND
#define DELETE_LINE_INSERT_COMMAND

#include "controller/command/command.h"


namespace VM {
    class DeleteLineInsertCommand: public ClonableCommand<Command, DeleteLineInsertCommand> {
        public:
        void doCommand(Controller &controller) override;

        DeleteLineInsertCommand(size_t quant): ClonableCommand<Command, DeleteLineInsertCommand>{quant} {}
        DeleteLineInsertCommand(const DeleteLineInsertCommand &other): ClonableCommand<Command, DeleteLineInsertCommand>{other} {}
        DeleteLineInsertCommand(DeleteLineInsertCommand &&other): ClonableCommand<Command, DeleteLineInsertCommand>{std::move(other)} {}
    };
}

#endif
