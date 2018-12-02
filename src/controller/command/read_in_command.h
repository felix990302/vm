#ifndef READ_IN_COMMAND_H
#define READ_IN_COMMAND_H

#include <string>
#include "model/buffer_type.h"
#include "undoable_command.h"


namespace VM {
    class ReadInCommand: public ClonableCommand<UndoableCommand, ReadInCommand> {
        std::string fileNameToReadFrom;
        BufferType contents;

        void commandHelper(Controller &controller) const;
        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &controller) const override;
        void redoTheCommand(Controller &controller) const override;

        public:
        ReadInCommand();
        ReadInCommand(const std::string &fileNameToWriteTo);
        ReadInCommand(const ReadInCommand &other);
        ReadInCommand(ReadInCommand &&other);
    };
}

#endif
