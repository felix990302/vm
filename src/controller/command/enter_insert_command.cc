#include "enter_insert_command.h"
#include "controller/controller.h"
#include "controller/insert_mode.h"


namespace VM {
    void EnterInsertCommand::doCommand(Controller &controller) {
        controller.changeMode(&controller.modes.insertMode);
    }

    std::unique_ptr<Command> EnterInsertCommand::clone() const {
        return std::make_unique<EnterInsertCommand>();
    }
}
