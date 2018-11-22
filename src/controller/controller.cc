#include "controller.h"
#include "mode.h"
#include "input.h"


namespace VM {
    void Controller::getAndProcessChar() {
        mode->processChar(input->getChar(), *fileBuffer);
    }

    const Input *Controller::getInput() {return input.get();}

    void Controller::changeBuffer(FileBuffer *newFileBuffer) {
        fileBuffer = newFileBuffer;
    }

    Controller::Controller(std::unique_ptr<Input> input, Mode *mode, FileBuffer *fileBuffer):
        input{std::move(input)},
        mode{mode},
        fileBuffer{fileBuffer}
    {}
}
