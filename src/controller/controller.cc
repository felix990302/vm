#include "controller.h"
#include "mode.h"
#include "input.h"


namespace VM {
    bool Controller::getAndProcessChar() {
        return mode->processChar(input->getChar());
    }

    Controller::Controller(std::unique_ptr<Input> input, FileBuffer *fileBuffer):
        input{std::move(input)},
        fileBuffer{fileBuffer},
        modes{*this},
        mode{&modes.commandMode}
    {}
}
