#include <memory>
#include "command_mode.h"
#include "controller/command/enter_insert_command.h"
#include "controller/command/move_command.h"
#include "controller/command/motion/direction_motion.h"


namespace VM {
    bool CommandMode::processChar(int c) { //FIXME: generalize parsing
        switch(c) {
            case 'h': {
                std::unique_ptr<Command> left = std::make_unique<MoveCommand>(1, std::make_unique<DirectionMotion<Direction::LEFT>>());
                left->doCommand(controller);
                break;
            }
            case 'l': {
                std::unique_ptr<Command> right = std::make_unique<MoveCommand>(1, std::make_unique<DirectionMotion<Direction::RIGHT>>());
                right->doCommand(controller);
                break;
            }
            case 'j': { // down
                std::unique_ptr<Command> down = std::make_unique<MoveCommand>(1, std::make_unique<DirectionMotion<Direction::DOWN>>());
                down->doCommand(controller);
                break;
            }
            case 'k': { // up
                std::unique_ptr<Command> up = std::make_unique<MoveCommand>(1, std::make_unique<DirectionMotion<Direction::UP>>());
                up->doCommand(controller);
                break;
            }
            case 'i': {
                std::unique_ptr<Command> enterInsert = std::make_unique<EnterInsertCommand>();
                enterInsert->doCommand(controller);
                break;
            }
        }

        return true;
    }   
}
