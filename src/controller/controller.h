#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "mode.h" // FIXME: should forward declare

class Input;
class FileBuffer;

namespace VM {
    struct Controller {
        std::unique_ptr<Input> input; 
        std::unique_ptr<Mode> mode;
        FileBuffer *fileBuffer;

        Controller(); // FIXME
        void getAndProcessChar();
    };
}

#endif
