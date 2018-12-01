#ifndef RIGHT_ENTER_INSERT_COMMAND
#define RIGHT_ENTER_INSERT_COMMAND

#include "controller/command/command.h"


namespace VM {
    class RightEnterInsertCommand: public ClonableCommand<Command, RightEnterInsertCommand> {
        public:
        void doCommand(Controller &controller) override;

        RightEnterInsertCommand(size_t quant): Clonable{quant} {}
        RightEnterInsertCommand(const RightEnterInsertCommand &other): Clonable{other} {}
        RightEnterInsertCommand(RightEnterInsertCommand &&other): Clonable{std::move(other)} {}
    };
}

#endif

