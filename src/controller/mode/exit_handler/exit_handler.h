#ifndef EXIT_HANDLER_H
#define EXIT_HANDLER_H

#include <memory>
#include <vector>
#include "controller/mode/mode.h"


namespace VM {
    class Controller;
    class MutationCommand;

    struct ExitHandler {
        size_t quantifier;

        virtual void postExit(Controller &controller, std::unique_ptr<MutationCommand> sequence) = 0;

        ExitHandler(size_t quantifer=1);
        virtual ~ExitHandler() = 0;
    };
}

#endif
