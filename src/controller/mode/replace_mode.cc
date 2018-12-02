#include <ncurses.h>
#include "model/file_buffer.h"
#include "controller/controller.h"
#include "controller/command/mutate_command/insert_command.h"
#include "controller/command/mutate_command/replace_command.h"
#include "controller/command/mutate_command/delete_forward_command.h"
#include "controller/command/mutation_command.h"
#include "controller/command/switch_command/escape_command.h"
#include "exit_handler/exit_handler.h"
#include "replace_mode.h"



namespace VM {
    void ReplaceMode::flush() {
        if(!insertBuffer.empty()) {
             exitHandler->postExit(controller, std::make_unique<MutationCommand>(1, std::move(insertBuffer)));
        }
        insertBuffer.clear();
    }

    void ReplaceMode::processChar(int c) {
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
            case 127: {
                if(!insertBuffer.empty()) {
                    insertBuffer.back()->undoCommand(controller);
                    insertBuffer.pop_back();
                    break;
                }

                [[fallthrough]];
            }
            case 27: { // FIXME: figure out how to handle escape
                controller.runSimpleCommand(std::make_unique<EscapeCommand>().get()); // or else flushing might not be recorded
                break;
            }
            case '\n': { // FIXME: figure out how to handle escape
                insertBuffer.push_back(std::make_unique<InsertCommand>('\n'));
                insertBuffer.back()->doCommand(controller);
                break;
            }
            default: {
                insertBuffer.push_back(std::make_unique<ReplaceCommand>(c));
                insertBuffer.back()->doCommand(controller);
            }
        }
    }

    std::string ReplaceMode::getStatusBarLeft() {
        return "-- REPLACE --";
    }

    void ReplaceMode::onExit() {
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::NormalModeCursor);
        flush();
    }

    void ReplaceMode::setExitHandler(std::unique_ptr<ExitHandler> handler) {
        exitHandler = std::move(handler);
    }

    ReplaceMode::ReplaceMode(Controller &controller) : Mode(controller) {}

    ReplaceMode::~ReplaceMode() {}
}
