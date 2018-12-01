#include "model/file_buffer.h"
#include "controller/controller.h"
#include "controller/mode/insert_mode.h"
#include "controller/mode/exit_handler/insert_handler.h"
#include "eol_enter_insert_command.h"


namespace VM {
    void EOLEnterInsertCommand::doCommand(Controller &controller) {
        auto &insertMode = controller.modes.insertMode;
        controller.changeMode(insertMode.get());
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        controller.getBuffer().ptrCursor.moveEndOfLine();
        insertMode->setExitHandler(std::make_unique<InsertHandler>(quant));
    }
}
