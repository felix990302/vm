#ifndef INSERT_HANDLER_H
#define INSERT_HANDLER_H

#include "exit_handler.h"


namespace VM {
    struct InsertHandler: public ExitHandler {
        void postExit(Controller &controller, std::unique_ptr<MutationCommand> sequence) override;
        
        InsertHandler(size_t quantifier): ExitHandler{quantifier} {}
    };
}

#endif
