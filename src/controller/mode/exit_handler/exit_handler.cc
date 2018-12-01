#include "exit_handler.h"


namespace VM {
    ExitHandler::ExitHandler(size_t quant): quantifier{quant} {}

    ExitHandler::~ExitHandler() {}
}
