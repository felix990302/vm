#include "model/file_buffer.h"
#include "controller/controller.h"
#include "controller/mode/insert_mode.h"
#include "controller/mode/exit_handler/insert_handler.h"
#include "right_enter_insert_command.h"


namespace VM {
    void RightEnterInsertCommand::doCommand(Controller &controller) {
        auto &insertMode = controller.modes.insertMode;
        controller.changeMode(insertMode.get());
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        controller.getBuffer().ptrCursor.moveRight();
        insertMode->setExitHandler(std::make_unique<InsertHandler>(quant));
    }
}
