#include <memory>
#include "controller/controller.h"
#include "controller/command/switch_command/escape_command.h"
#include "lazy_command_mode.h"


namespace VM {
    void LazyCommandMode::processChar(int c) {
        switch(c) {
            case '\n': { // enter
                flush();
                /* fallthrough */
            }
            case 27: { // esc
                controller.runCommand(std::make_unique<EscapeCommand>());
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

    std::string LazyCommandMode::getStatusBarLeft() {
        return getStatusBarLeftIndicatorChar() + commandString;
    }
}
