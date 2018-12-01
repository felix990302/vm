#ifndef EOL_ENTER_INSERT_COMMAND
#define EOL_ENTER_INSERT_COMMAND

#include "controller/command/command.h"


namespace VM {
    class EOLEnterInsertCommand: public ClonableCommand<Command, EOLEnterInsertCommand> {
        public:
        void doCommand(Controller &controller) override;

        EOLEnterInsertCommand(size_t quant): Clonable{quant} {}
        EOLEnterInsertCommand(const EOLEnterInsertCommand &other): Clonable{other} {}
        EOLEnterInsertCommand(EOLEnterInsertCommand &&other): Clonable{std::move(other)} {}
    };
}

#endif
