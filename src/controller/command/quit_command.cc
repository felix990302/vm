#include "controller/controller.h"
#include "quit_command.h"


namespace VM {
    void QuitCommand::doCommand(Controller &controller) {
        if(!shouldForce && !controller.getUndoStack().empty()) {
            throw ProgramQuitException {}; // FIXME: possible issue with macros
        }

        controller.setProgramIsRunning(false);
    }

    std::unique_ptr<Command> QuitCommand::clone() const {
        return std::make_unique<QuitCommand>(*this);
    }
}
