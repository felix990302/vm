#ifndef BOL_ENTER_INSERT_COMMAND
#define BOL_ENTER_INSERT_COMMAND

#include "controller/command/command.h"


namespace VM {
    class BOLEnterInsertCommand: public ClonableCommand<Command, BOLEnterInsertCommand> {
        public:
        void doCommand(Controller &controller) override;

        BOLEnterInsertCommand(size_t quant): Clonable{quant} {}
        BOLEnterInsertCommand(const BOLEnterInsertCommand &other): Clonable{other} {}
        BOLEnterInsertCommand(BOLEnterInsertCommand &&other): Clonable{std::move(other)} {}
    };
}

#endif
