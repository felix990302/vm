#ifndef YankCommand_H
#define YankCommand_H

#include "model/buffer_type.h"
#include "model/file_buffer.h"
#include "model/ptr_cursor.h"
#include "controller/command/motion/motion.h"
#include "controller/command/undoable_command.h"
#include "controller/controller.h"

namespace VM {


    class YankCommand : public ClonableCommand <Command, YankCommand>{
        std::unique_ptr<Motion> motion;
    public:
        void doCommand(Controller &controller) override;

        YankCommand(size_t quant, std::unique_ptr<Motion> motion);
        YankCommand(const YankCommand &other);
        YankCommand(YankCommand &&other);
    };
}


#endif
