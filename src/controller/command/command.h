#ifndef COMMAND_H
#define COMMAND_H

#include <memory>


namespace VM {
    class Cursor;
    class FileBuffer;

    class Command {
        const size_t quant;

        protected:
        virtual void doTheCommand(FileBuffer &filebuffer) const = 0;
        virtual void doTheSideEffect(FileBuffer &filebuffer) = 0;

        public:
        void doCommand(FileBuffer &fileBuffer);

        Command(const size_t &quant);
        virtual std::unique_ptr<Command> clone() const = 0;
        virtual ~Command() = 0;
    };
}

#endif
