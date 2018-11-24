#include <ncurses.h>
#include "model/file_buffer.h"
#include "insert_mode.h"
#include "command/insert_command.h"



namespace VM {
    void InsertMode::processChar(int c) {
        switch(c) {
            case KEY_ENTER: {
                std::unique_ptr<Command> newline = std::make_unique<InsertCommand<'\n'>> (1, '\n');
                newline->doCommand(controller);
                break;
            }
            default: {
                std::unique_ptr<Command> insert = std::make_unique<InsertCommand<'\0'>> (1, c);
                insert->doCommand(controller);
            }
        }
    }   
}
