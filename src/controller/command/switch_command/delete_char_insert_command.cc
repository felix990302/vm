#include "controller/mode/insert_mode.h"
#include "controller/mode/exit_handler/delete_insert_handler.h"
#include "controller/controller.h"
#include "model/file_buffer.h"
#include "controller/command/mutate_command/delete_forward_command.h"
#include "delete_char_insert_command.h"


namespace VM {
    void DeleteCharInsertCommand::doCommand(Controller &controller) {
        PtrCursor &cursor = controller.getBuffer().ptrCursor;
        InsertMode &insertMode = *controller.modes.insertMode;

        for(size_t j=0; j<quant; ++j) {
            if(!cursor.isEOL()) {
                insertMode.getInserBuffer().push_back(std::make_unique<DeleteForwardCommand>(1));
                insertMode.getInserBuffer().back()->doCommand(controller);
            }
        }

        controller.changeMode(controller.modes.insertMode.get());
        insertMode.setExitHandler(std::make_unique<DeleteInsertHandler>(quant));
    }
}
