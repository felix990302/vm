#ifndef JOINLINES_H
#define JOINLINES_H
#include "undoable_command.h"
#include "model/file_buffer.h"
namespace VM {


    class JoinLines: public ClonableCommand<UndoableCommand, JoinLines> {
        std::vector<Cursor> positions;
        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &controller) const override;
        void redoTheCommand(Controller &controller) const override;
        bool isLineBelow;
    public:
        JoinLines(int quant): Clonable{static_cast<size_t>(quant)}, isLineBelow{false}{}
        JoinLines(const JoinLines &other): Clonable{other}, isLineBelow{other.isLineBelow}{}
        JoinLines(JoinLines &&other): Clonable{std::move(other)}, isLineBelow{other.isLineBelow} {}
    };
}


#endif
