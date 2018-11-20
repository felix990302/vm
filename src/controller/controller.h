#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

class Input;
class Mode;
class FileBuffer;

namespace VM {
    struct Controller {
        std::unique_ptr<Input> input; 
        std::unique_ptr<Mode> mode;
        FileBuffer *fileBuffer;

        Controller(std::unique_ptr<Input> input, std::unique_ptr<Mode> mode);
        void getAndProcessChar();
    };
}

#endif
