#include <memory>
#include "controller/controller.h"
#include "controller/command/switch_command/escape_command.h"
#include "lazy_command_mode.h"
#include "ncurses.h"


namespace VM {
    void LazyCommandMode::processChar(int c) {
        switch(c) {
            case '\n': { // enter
                flush();
                /* fallthrough */
            }
            case 27: { // esc
                controller.runSimpleCommand(std::make_unique<EscapeCommand>());
                break;
            }
            case KEY_BACKSPACE:
            case 127: //linux is weired TODO
            {
                if(commandString.size()) commandString.pop_back();
                else controller.runSimpleCommand(std::make_unique<EscapeCommand>());
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
