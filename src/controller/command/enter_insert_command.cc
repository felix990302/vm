#include "enter_insert_command.h"
#include "controller/controller.h"
#include "controller/insert_mode.h"


namespace VM {
    void EnterInsertCommand::doTheCommand(Controller &controller) const {
        controller.changeMode(&InsertMode::Instance());
    }

    void EnterInsertCommand::doTheSideEffect(Controller &controller) {}

    std::unique_ptr<Command> EnterInsertCommand::clone() const {
        return std::make_unique<EnterInsertCommand>();
    }
}
