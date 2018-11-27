#include <ncurses.h>
#include "model/file_buffer.h"
#include "controller/controller.h"
#include "controller/command/mutate_command/insert_newline_command.h"
#include "controller/command/mutation_command.h"
#include "controller/command/escape_command.h"
#include "insert_mode.h"



namespace VM {
    void InsertMode::flush() {
        if(!undoBuffer.empty()) {
             controller.getUndoStack().emplace(std::make_unique<MutationCommand>(1, std::move(undoBuffer)));
        }
    }

    void InsertMode::processChar(int c) {
        switch(c) {
            case '\n': {
                undoBuffer.push_back(std::make_unique<InsertNewlineCommand>(1));
                undoBuffer.back()->doCommand(controller);
                break;
            }
            case 27: { // FIXME: figure out how to handle escape
                std::unique_ptr<Command> esc = std::make_unique<EscapeCommand>();
                esc->doCommand(controller);
                break;
            }
            default: {
                undoBuffer.push_back(std::make_unique<InsertCommand>(1, c));
                undoBuffer.back()->doCommand(controller);
            }
        }
    }

    std::string InsertMode::getStatusBarLeft() {
        return "-- INSERT --";
    }
}
