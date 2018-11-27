#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <memory>
#include "command.h"


namespace VM {
    class Motion;

    class MoveCommand: public ClonableCommand<Command, MoveCommand> {
        protected:
        std::unique_ptr<Motion> motion;

        public:
        void doCommand(Controller &controller) override;

        MoveCommand(size_t quant, std::unique_ptr<Motion> motion);
        template<typename M, typename ...Args>MoveCommand(size_t quant, Args &&...args): // no idea if this actually works
            Clonable{quant},
            motion{std::make_unique<M>(quant, std::forward<Args>(args)...)}
        {}
        MoveCommand(const MoveCommand &other);
        MoveCommand(MoveCommand &&other);
    };
}

#endif
