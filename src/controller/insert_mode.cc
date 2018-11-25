#include <ncurses.h>
#include "model/file_buffer.h"
#include "insert_mode.h"
#include "command/mutate_command/insert_newline_command.h"



namespace VM {
    void InsertMode::processChar(int c) {
        switch(c) {
            case '\n': {
                std::unique_ptr<Command> newline = std::make_unique<InsertNewlineCommand> (1);
                newline->doCommand(controller);
                break;
            }
            default: {
                std::unique_ptr<Command> insert = std::make_unique<InsertCommand> (1, c);
                insert->doCommand(controller);
            }
        }
    }   
}
