#ifndef EOL_HANDLER_H
#define EOL_HANDLER_H

#include "exit_handler.h"


namespace VM {
    struct EOLHandler: public ExitHandler {
        void postExit(Controller &controller, std::unique_ptr<MutationCommand> sequence) override;
        
        EOLHandler(size_t quantifier): ExitHandler{quantifier} {}
    };
}

#endif
