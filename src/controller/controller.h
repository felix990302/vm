#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

class Input;
class Mode;
class FileBuffer;

namespace VM {
    class Controller {
        std::unique_ptr<Input> input; 
        std::unique_ptr<Mode> mode;
        FileBuffer *fileBuffer;

        public:
        virtual void getAndProcessChar() = 0;
    };
}

#endif
