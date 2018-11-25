#include <ncurses.h>
#include "model/file_buffer.h"
#include "controller.h"
#include "insert_mode.h"
#include "command/mutate_command/insert_newline_command.h"
#include "command/escape_command.h"



namespace VM {
    bool InsertMode::processChar(int c) {
        switch(c) {
            case '\n': {
                std::unique_ptr<UndoableCommand> newline = std::make_unique<InsertNewlineCommand>(1);
                newline->doCommand(controller);
                break;
            }
            case 27: { // FIXME: figure out how to handle escape
                std::unique_ptr<Command> esc = std::make_unique<EscapeCommand>();
                esc->doCommand(controller);
                break;
            }
            default: {
                std::unique_ptr<UndoableCommand> insert = std::make_unique<InsertCommand>(1, c);
                insert->doCommand(controller);
            }
        }

        return true;
    }   
}
