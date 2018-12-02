#include "controller/controller.h"
#include "toggle_record_macro_command.h"


namespace VM {
    void ToggleRecordMacroCommand::doCommand(Controller &controller) {
        if(controller.getMacroRecKey()) controller.setMacroRecKey(0);
        else {
            controller.getMacroMap()[key].clear();
            controller.setMacroRecKey(key);
        }
    }
}
