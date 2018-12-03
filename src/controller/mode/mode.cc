#include "mode.h"
#include "controller/controller.h"

namespace VM {
    Mode::~Mode() {}

    std::string Mode::getStatusBarLeft() {
        if(controller.getMacroRecKey() != 0)
            return std::string(" recording @") + controller.getMacroRecKey() ;
        return  "";
    }

    std::string Mode::getStatusBarRight() {
        return "";
    }

    int Mode::getStatusBarCursor() {
        return -1;
    }
}
