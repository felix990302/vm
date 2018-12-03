#ifndef OPEN_LINE_COMMAND_H
#define OPEN_LINE_COMMAND_H

#include "controller/command/motion/direction.h"
#include "model/file_buffer.h"
#include "controller/controller.h"
#include "mutate_command.h"


namespace VM {
    template<Direction dir> class OpenLineCommand;

    template<>class OpenLineCommand<Direction::DOWN>: public ClonableCommand<MutateCommand, OpenLineCommand<Direction::DOWN>> {
        void commandHelper(Controller &controller) const {
            PtrCursor &cursor = controller.getBuffer().ptrCursor;
            cursor.setType(PtrCursor::CursorMovement::IteratorCursor);
            cursor.moveEndOfLine();
            controller.getBuffer().typeNewLine();
        }

        void doTheCommand(Controller &controller) override {
            commandHelper(controller);
        }

        void undoTheCommand(Controller &controller) const override {
            controller.getBuffer().delete_backward(1);
        }

        void redoTheCommand(Controller &controller) const override {
            commandHelper(controller);
        }

        public:

        OpenLineCommand(size_t quant=1): Clonable{quant, '\n'} {}
        OpenLineCommand(const OpenLineCommand &other): Clonable{other} {}
        OpenLineCommand(OpenLineCommand &&other): Clonable{std::move(other)} {}
    };

    template<>class OpenLineCommand<Direction::UP>: public ClonableCommand<MutateCommand, OpenLineCommand<Direction::UP>> {
        void commandHelper(Controller &controller) const {
            PtrCursor &cursor = controller.getBuffer().ptrCursor;
            cursor.moveBeginOfLine();
            controller.getBuffer().typeNewLine();
            cursor.moveUp();
        }

        void doTheCommand(Controller &controller) override {
            commandHelper(controller);
        }

        void undoTheCommand(Controller &controller) const override {
            PtrCursor &cursor = controller.getBuffer().ptrCursor;
            cursor.moveDown();
            controller.getBuffer().delete_backward(1);
        }

        void redoTheCommand(Controller &controller) const override {
            commandHelper(controller);
        }

        public:

        OpenLineCommand(size_t quant=1): Clonable{quant, '\n'} {}
        OpenLineCommand(const OpenLineCommand &other): Clonable{other} {}
        OpenLineCommand(OpenLineCommand &&other): Clonable{std::move(other)} {}
    };
}
#endif

