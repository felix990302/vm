#ifndef DELETE_INSERT_HANDLER_H
#define DELETE_INSERT_HANDLER_H

#include "exit_handler.h"


namespace VM {
    struct DeleteInsertHandler: public ExitHandler {
        void postExit(Controller &controller, std::unique_ptr<MutationCommand> sequence) override;
        
        DeleteInsertHandler(size_t quantifier): ExitHandler{quantifier} {}
    };
}

#endif
