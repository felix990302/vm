#include "insert_backward_command.h"
#include "model/file_buffer.h"


namespace VM {
    void InsertBackwardCommand::doTheCommand(FileBuffer &fileBuffer) const {
        fileBuffer.type(getToMutate());
    }

    void InsertBackwardCommand::doTheSideEffect(FileBuffer &fileBuffer) {
        setCursor(fileBuffer.ptrCursor);
    }

    void InsertBackwardCommand::undoTheCommand(FileBuffer &fileBuffer) const {
        fileBuffer.delete_backward(getToMutate().size());
    }

    std::unique_ptr<Command> InsertBackwardCommand::clone() const {
        return std::make_unique<InsertBackwardCommand>(*this);
    }

    InsertBackwardCommand::InsertBackwardCommand(const size_t &quant, const std::string &toInsert):
        MutateCommand{quant, toInsert}
    {}

    InsertBackwardCommand::InsertBackwardCommand(const InsertBackwardCommand &other): MutateCommand{other} {}

    InsertBackwardCommand::InsertBackwardCommand(InsertBackwardCommand &&other): MutateCommand{std::move(other)} {}
}

