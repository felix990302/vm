#include <memory>
#include "controller/command/escape_command.h"
#include "lazy_command_mode.h"


namespace VM {
    void LazyCommandMode::processChar(int c) {
        switch(c) {
            case '\n': { // enter
                flush();
                // PURPOSELY FALL THROUGH
            }
            case 27: { // esc
                std::unique_ptr<Command> esc = std::make_unique<EscapeCommand>();
                esc->doCommand(controller);
                break;
            }
            default: {
                commandString.push_back(c);
            }
        }
    } 

    void LazyCommandMode::onExit() {
        commandString.clear();
    }

    LazyCommandMode::~LazyCommandMode() {}
}
