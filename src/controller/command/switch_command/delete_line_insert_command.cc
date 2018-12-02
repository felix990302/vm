#include "controller/mode/insert_mode.h"
#include "controller/mode/exit_handler/delete_insert_handler.h"
#include "controller/controller.h"
#include "model/file_buffer.h"
#include "controller/command/mutate_command/delete_forward_command.h"
#include "delete_line_insert_command.h"


namespace VM {
    void DeleteLineInsertCommand::doCommand(Controller &controller) {
        PtrCursor &cursor = controller.getBuffer().ptrCursor;

        controller.changeMode(controller.modes.insertMode.get());
        InsertMode &insertMode = *controller.modes.insertMode;

        cursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        cursor.moveBeginOfLine();
        size_t origSize = cursor.getLineIterator()->size();
        for(size_t k=0; k<origSize; ++k) {
            insertMode.getInserBuffer().push_back(std::make_unique<DeleteForwardCommand>(1));
            insertMode.getInserBuffer().back()->doCommand(controller);
        }
        
        for(size_t j=1; j<quant; ++j) {
            if(!cursor.isEOF()) {
                insertMode.getInserBuffer().push_back(std::make_unique<DeleteForwardCommand>(1));
                insertMode.getInserBuffer().back()->doCommand(controller);
            }
            size_t origSize = cursor.getLineIterator()->size();
            for(size_t k=0; k<origSize; ++k) {
                insertMode.getInserBuffer().push_back(std::make_unique<DeleteForwardCommand>(1));
                insertMode.getInserBuffer().back()->doCommand(controller);
            }
        }

        insertMode.setExitHandler(std::make_unique<DeleteInsertHandler>(quant));
    }
}
