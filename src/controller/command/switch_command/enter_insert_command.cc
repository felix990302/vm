#include "controller/controller.h"
#include "controller/mode/exit_handler/insert_handler.h"
#include "controller/mode/insert_mode.h"
#include "enter_insert_command.h"


namespace VM {
    void EnterInsertCommand::doCommand(Controller &controller) {
        controller.changeMode(controller.modes.insertMode.get());
        controller.modes.insertMode->setExitHandler(std::make_unique<InsertHandler>(quant));
    }
}
