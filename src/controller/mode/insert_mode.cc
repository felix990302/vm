#include <ncurses.h>
#include "model/file_buffer.h"
#include "controller/controller.h"
#include "controller/command/mutate_command/insert_newline_command.h"
#include "controller/command/mutate_command/delete_backward_command.h"
#include "controller/command/mutate_command/delete_forward_command.h"
#include "controller/command/mutation_command.h"
#include "controller/command/switch_command/escape_command.h"
#include "insert_mode.h"



namespace VM {
    void InsertMode::flush() {
        if(!insertBuffer.empty()) {
             controller.pushCommand(std::make_unique<MutationCommand>(1, std::move(insertBuffer)));
        }
    }

    void InsertMode::processChar(int c) {

        switch(c) {
            case KEY_DC:{
                undoBuffer.push_back(std::make_unique<DeleteForwardCommand>(1));
                undoBuffer.back()->doCommand(controller);
                break;
            }
            case KEY_BACKSPACE:
            case 127: //linux is weired TODO
                {
                undoBuffer.push_back(std::make_unique<DeleteBackwardCommand>(1));
                undoBuffer.back()->doCommand(controller);
                break;
            }
            case '\n': {
                insertBuffer.push_back(std::make_unique<InsertNewlineCommand>(1));
                insertBuffer.back()->doCommand(controller);
                break;
            }
            case 27: { // FIXME: figure out how to handle escape
                controller.runCommand(std::make_unique<EscapeCommand>()); // or else flushing might not be recorded
                break;
            }
            default: {
                insertBuffer.push_back(std::make_unique<InsertCommand>(1, c));
                insertBuffer.back()->doCommand(controller);
            }
        }
    }

    std::string InsertMode::getStatusBarLeft() {
        return "-- INSERT --";
    }

    void InsertMode::onExit() {
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::NormalModeCursor);
        flush();
    }

    InsertMode::InsertMode(Controller &controller) : Mode(controller) {
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::InsertModeCursor);
    }
}
