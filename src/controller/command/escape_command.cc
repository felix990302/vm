#include "escape_command.h"
#include "controller/controller.h"


namespace VM {
    void EscapeCommand::doCommand(Controller &controller) {
        controller.getMode().onExit();
        controller.changeMode(&controller.modes.commandMode);
    }

    std::unique_ptr<Command> EscapeCommand::clone() const {
        return std::make_unique<EscapeCommand>(*this);
    }
}
