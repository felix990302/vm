#include "enter_colon_command.h"
#include "controller/controller.h"
#include "controller/mode/lazy_command_mode/colon_command_mode.h"


namespace VM {
    void EnterColonCommand::doCommand(Controller &controller) {
        controller.changeMode(controller.modes.colonCommandMode.get());
    }
}
