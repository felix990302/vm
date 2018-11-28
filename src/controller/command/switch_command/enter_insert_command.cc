#include "enter_insert_command.h"
#include "controller/controller.h"
#include "controller/mode/insert_mode.h"


namespace VM {
    void EnterInsertCommand::doCommand(Controller &controller) {
        controller.changeMode(controller.modes.insertMode.get());
    }
}
