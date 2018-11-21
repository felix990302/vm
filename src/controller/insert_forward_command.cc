#include "insert_forward_command.h"
#include "model/file_buffer.h"


namespace VM {
    void InsertForwardCommand::doTheCommand(FileBuffer &fileBuffer) const {
        fileBuffer.type(getToMutate());
    }

    void InsertForwardCommand::doTheSideEffect(FileBuffer &fileBuffer) {
        setCursor(fileBuffer.ptrCursor);
    }

    void InsertForwardCommand::undoTheCommand(FileBuffer &fileBuffer) const {
        fileBuffer.delete_forward(getToMutate().size());
    }

    std::unique_ptr<Command> InsertForwardCommand::clone() const {
        return std::make_unique<InsertForwardCommand>(*this);
    }

    InsertForwardCommand::InsertForwardCommand(const size_t &quant, const std::string &toInsert):
        MutateCommand{quant, toInsert}
    {}

    InsertForwardCommand::InsertForwardCommand(const InsertForwardCommand &other): MutateCommand{other} {}

    InsertForwardCommand::InsertForwardCommand(InsertForwardCommand &&other): MutateCommand{std::move(other)} {}
}
