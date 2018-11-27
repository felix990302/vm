#include "mode.h"


namespace VM {
    Mode::~Mode() {}

    std::string Mode::getStatusBarLeft() {
        return "";
    }

    std::string Mode::getStatusBarRight() {
        return "";
    }
}
