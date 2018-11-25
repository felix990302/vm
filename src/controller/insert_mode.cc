#include <ncurses.h>
#include "model/file_buffer.h"
#include "controller.h"
#include "insert_mode.h"
#include "command/mutate_command/insert_newline_command.h"



namespace VM {
    bool InsertMode::processChar(int c) {
        switch(c) {
            case KEY_UP: {
                controller.getBuffer()->ptrCursor.moveUp();
                controller.getBuffer()->ptrCursor.moveRight(0); // FIXME: proper way to garantee cursor is valid position
                break;
            }
            case KEY_DOWN: {
                controller.getBuffer()->ptrCursor.moveDown();
                controller.getBuffer()->ptrCursor.moveRight(0); // FIXME: proper way to garantee cursor is valid position
                break;
            }
            case KEY_LEFT: {
                controller.getBuffer()->ptrCursor.moveLeft();
                break;
            }
            case KEY_RIGHT: {
                controller.getBuffer()->ptrCursor.moveRight();
                break;
            }
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

        return true;
    }   
}
