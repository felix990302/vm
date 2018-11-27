#include "controller/controller.h"
#include "quit_command.h"


namespace VM {
    void QuitCommand::doCommand(Controller &controller) {
        controller.quit(shouldForce);
    }
}
