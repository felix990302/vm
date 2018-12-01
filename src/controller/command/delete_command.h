#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "undoable_command.h"
#include "motion/motion.h"
#include <string>


namespace VM {

    class DeleteCommand : public ClonableCommand <UndoableCommand, DeleteCommand>{
        std::string buffer;
        Cursor beginPosition; // this position is acutally the position where we strt deleting, begining of line for multiline commands
        bool isMultiline;

        std::unique_ptr<Motion> motion;

        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &) const override;
        void redoTheCommand(Controller &controller) const override;

    public:
        DeleteCommand(size_t quant, std::unique_ptr<Motion> motion);
        DeleteCommand(const DeleteCommand &other);
        DeleteCommand(DeleteCommand &&other);
    };

}


#endif
