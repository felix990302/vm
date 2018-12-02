#include "controller/controller.h"
#include "controller/mode/exit_handler/insert_handler.h"
#include "controller/mode/replace_mode.h"
#include "enter_replace_command.h"


namespace VM {
    void EnterReplaceCommand::doCommand(Controller &controller) {
        controller.changeMode(controller.modes.replaceMode.get());
        controller.modes.replaceMode->setExitHandler(std::make_unique<InsertHandler>(quant));
    }
}
