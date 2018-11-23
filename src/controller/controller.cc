#include "controller.h"
#include "mode.h"
#include "input.h"


namespace VM {
    void Controller::getAndProcessChar() {
        mode->processChar(input->getChar(), *this);
    }

    Controller::Controller(std::unique_ptr<Input> input, Mode *mode, FileBuffer *fileBuffer):
        input{std::move(input)},
        mode{mode},
        fileBuffer{fileBuffer}
    {}
}
