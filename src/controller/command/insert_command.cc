#include "insert_command.h"
#include "model/file_buffer.h"


namespace VM {
    void InsertCommand::doTheCommand(FileBuffer &fileBuffer) const {
        fileBuffer.type(getToMutate());
    }

    void InsertCommand::doTheSideEffect(FileBuffer &fileBuffer) {
        setCursor(fileBuffer.ptrCursor);
    }

    void InsertCommand::undoTheCommand(FileBuffer &fileBuffer) const {
        fileBuffer.delete_forward(getToMutate().size());
    }

    std::unique_ptr<Command> InsertCommand::clone() const {
        return std::make_unique<InsertCommand>(*this);
    }

    InsertCommand::InsertCommand(size_t quant, const std::string &toInsert):
        MutateCommand{quant, toInsert}
    {}

    InsertCommand::InsertCommand(size_t quant, char c):
        MutateCommand{quant, c}
    {}

    InsertCommand::InsertCommand(const InsertCommand &other): MutateCommand{other} {}

    InsertCommand::InsertCommand(InsertCommand &&other): MutateCommand{std::move(other)} {}
}
