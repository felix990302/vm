#include "controller/controller.h"
#include "quit_command.h"


namespace VM {
    void QuitCommand::doCommand(Controller &controller) {
        controller.quit(shouldForce);
    }

    std::unique_ptr<Command> QuitCommand::clone() const {
        return std::make_unique<QuitCommand>(*this);
    }
}
