#include <memory>
#include "controller/command/escape_command.h"
#include "lazy_command_mode.h"


namespace VM {
    void LazyCommandMode::processChar(int c) {
        switch(c) {
            case '\n': { // enter
                flush();
                std::unique_ptr<Command> esc = std::make_unique<EscapeCommand>();
                esc->doCommand(controller);
                break;
            }
            case 27: { // esc
                std::unique_ptr<Command> esc = std::make_unique<EscapeCommand>();
                esc->doCommand(controller);
                break;
            }
            default: {
                inputBuffer.push_back(c);
            }
        }
    } 

    void LazyCommandMode::onExit() {
        inputBuffer.clear();
    }

    LazyCommandMode::~LazyCommandMode() {}
}
