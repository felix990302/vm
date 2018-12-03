#include <ncurses.h>
#include "model/file_buffer.h"
#include "controller/controller.h"
#include "controller/command/mutate_command/insert_command.h"
#include "controller/command/mutate_command/delete_backward_command.h"
#include "controller/command/mutate_command/delete_forward_command.h"
#include "controller/command/mutation_command.h"
#include "controller/command/switch_command/escape_command.h"
#include "exit_handler/exit_handler.h"
#include "insert_mode.h"



namespace VM {
    void InsertMode::flush() {
        if(!insertBuffer.empty()) {
             exitHandler->postExit(controller, std::make_unique<MutationCommand>(1, std::move(insertBuffer)));
        }
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::NormalModeCursor);
        controller.setMessage("");
        insertBuffer.clear();
    }

    void InsertMode::processChar(int c) {
        PtrCursor &cursor = controller.getBuffer().ptrCursor;
        cursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        switch(c) {
            case KEY_DC:{
                if(cursor.getLineIterator()!=cursor.getLineEnd()-1 || cursor.getStringIterator()!=cursor.getLineIterator()->end()) {
                    insertBuffer.push_back(std::make_unique<DeleteForwardCommand>(1));
                    insertBuffer.back()->doCommand(controller);
                } 
                break;
            }
            case KEY_BACKSPACE:
            case 127:
                {
                if(controller.getBuffer().ptrCursor.getLine()>0 || controller.getBuffer().ptrCursor.getCol()>0) {
                    insertBuffer.push_back(std::make_unique<DeleteBackwardCommand>(1));
                    insertBuffer.back()->doCommand(controller);
                }
                break;
            }
            case 27: { // FIXME: figure out how to handle escape
                controller.runSimpleCommand(std::make_unique<EscapeCommand>().get()); // or else flushing might not be recorded
                break;
            }
            default: {
                insertBuffer.push_back(std::make_unique<InsertCommand>(c));
                insertBuffer.back()->doCommand(controller);
            }
        }
    }

    std::string InsertMode::getStatusBarLeft() {
        return "-- INSERT --" + Mode::getStatusBarLeft();
    }

    void InsertMode::onExit() {

        flush();
    }

    void InsertMode::setExitHandler(std::unique_ptr<ExitHandler> handler) {
        exitHandler = std::move(handler);
    }

    InsertMode::InsertMode(Controller &controller) : Mode(controller) {}

    InsertMode::~InsertMode() {}
}
