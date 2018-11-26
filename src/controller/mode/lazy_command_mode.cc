#include <memory>
#include "controller/command/escape_command.h"
#include "lazy_command_mode.h"


namespace VM {
    void LazyCommandMode::processChar(int c) {
        switch(c) {
            case '\n': {
                std::unique_ptr<Command> esc = std::make_unique<EscapeCommand>();
                esc->doCommand(controller);
                break;
            }
        }
    } 

    LazyCommandMode::~LazyCommandMode() {}
}
