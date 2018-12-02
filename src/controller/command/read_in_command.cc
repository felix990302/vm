#include "controller/controller.h"
#include "model/file_buffer.h"
#include "read_in_command.h"


namespace VM {
    void ReadInCommand::commandHelper(Controller &controller) const {
        auto &cursor = controller.getBuffer().ptrCursor;
        auto &fileBuffer = controller.getBuffer().getBuffer();
        fileBuffer.insert(cursor.getLineIterator()+1, contents.begin(), contents.end());
    }

    void ReadInCommand::doTheCommand(Controller &controller) {
        if(fileNameToReadFrom.empty()) {
            contents = make_bufferType(controller.getBuffer().getFileName());
        }
        else {
            contents = make_bufferType(fileNameToReadFrom);
        }

        commandHelper(controller);
    }

    void ReadInCommand::undoTheCommand(Controller &controller) const {
        auto &cursor = controller.getBuffer().ptrCursor;
        auto &fileBuffer = controller.getBuffer().getBuffer();
        fileBuffer.erase(cursor.getLineIterator()+1, cursor.getLineIterator()+contents.size()+1);
    }

    void ReadInCommand::redoTheCommand(Controller &controller) const {
        commandHelper(controller);
    }

    ReadInCommand::ReadInCommand():
        Clonable{quant},
        fileNameToReadFrom{},
        contents{}
    {}

    ReadInCommand::ReadInCommand(const std::string &fileNameToReadFrom):
        Clonable{quant},
        fileNameToReadFrom{fileNameToReadFrom},
        contents{}
    {}

    ReadInCommand::ReadInCommand(const ReadInCommand &other):
        Clonable{other.quant},
        fileNameToReadFrom{other.fileNameToReadFrom},
        contents{other.contents}
    {}

    ReadInCommand::ReadInCommand(ReadInCommand &&other):
        Clonable{std::move(quant)},
        fileNameToReadFrom{std::move(other.fileNameToReadFrom)},
        contents{std::move(other.contents)}
    {}
}
