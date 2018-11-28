#include "controller/mode/command_mode.h"
#include "controller/controller.h"
#include "escape_command.h"


namespace VM {
    void EscapeCommand::doCommand(Controller &controller) {
        controller.getMode().onExit();
        controller.changeMode(controller.modes.commandMode.get());
    }
}
