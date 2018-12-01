#include "model/file_buffer.h"
#include "controller/controller.h"
#include "controller/mode/insert_mode.h"
#include "controller/mode/exit_handler/insert_handler.h"
#include "bol_enter_insert_command.h"


namespace VM {
    void BOLEnterInsertCommand::doCommand(Controller &controller) {
        auto &insertMode = controller.modes.insertMode;
        controller.changeMode(insertMode.get());
        controller.getBuffer().ptrCursor.moveBeginOfLine();
        insertMode->setExitHandler(std::make_unique<InsertHandler>(quant));
    }
}
