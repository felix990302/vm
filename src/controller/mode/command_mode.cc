#include <memory>
#include "command_mode.h"
#include "controller/command/enter_insert_command.h"


namespace VM {
    bool CommandMode::processChar(int c) { //FIXME: generalize parsing
        switch(c) {
            case 'i': {
                std::unique_ptr<Command> insert = std::make_unique<EnterInsertCommand>();
                insert->doCommand(controller);
            }
        }

        return true;
    }   
}
