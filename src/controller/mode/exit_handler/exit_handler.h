#ifndef EXIT_HANDLER_H
#define EXIT_HANDLER_H

#include <memory>
#include <vector>
#include "controller/mode/mode.h"


namespace VM {
    class Controller;
    class MutationCommand;

    class ExitHandler {
        size_t quantifier;

        public:
        virtual void postExit(Controller &controller, std::unique_ptr<MutationCommand> sequence) = 0;

        virtual ~ExitHandler() = 0;
    };
}

#endif
