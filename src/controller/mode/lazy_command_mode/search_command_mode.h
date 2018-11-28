#ifndef SEARCH_COMMAND_MODE_H
#define SEARCH_COMMAND_MODE_H

#include <memory>
#include "controller/controller.h"
#include "controller/command/motion/search_motion.h"
#include "controller/command/move_command.h"
#include "lazy_command_mode.h"


namespace VM {
    template<Direction dir> class SearchCommandMode: public LazyCommandMode {
        public:
        void flush() override {
           controller.runCommand(
                   std::make_unique<MoveCommand>(
                       1,
                       std::make_unique<SearchMotion<dir>>(1, commandString)
                   )
           );
        }

        SearchCommandMode(Controller &controller): LazyCommandMode{controller} {}
    };
}

#endif
