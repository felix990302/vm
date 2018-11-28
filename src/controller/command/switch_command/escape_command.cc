#include "escape_command.h"
#include "controller/controller.h"


namespace VM {
    void EscapeCommand::doCommand(Controller &controller) {
        controller.getMode().onExit();
        controller.changeMode(&controller.modes.commandMode);
    }
}
