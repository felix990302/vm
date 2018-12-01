#ifndef OPEN_LINE_HANDLER_H
#define OPEN_LINE_HANDLER_H

#include "exit_handler.h"


namespace VM {
    struct OpenLineHandler: public ExitHandler {
        void postExit(Controller &controller, std::unique_ptr<MutationCommand> sequence) override;
        
        OpenLineHandler(size_t quantifier): ExitHandler{quantifier} {}
    };
}

#endif
