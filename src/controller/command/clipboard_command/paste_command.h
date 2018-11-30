#ifndef PASTE_COMMAND_H
#define PASTE_COMMAND_H

#include "model/file_buffer.h"
#include "controller/controller.h"
#include "controller/command/undoable_command.h"
#include "controller/command/motion/direction.h"


namespace VM {
    template<Direction dir> class PasteCommand;

    template<> class PasteCommand<Direction::RIGHT>: public ClonableCommand<UndoableCommand, PasteCommand<Direction::RIGHT>> {
        BufferType toPaste;
        bool shouldPasteInline;

        void commandHelper(Controller &controller) const {
            std::string restOfLine {""};
            PtrCursor &cursor = controller.getBuffer().ptrCursor;
            BufferType &buffer = controller.getBuffer().getBuffer();

            if(shouldPasteInline) {
                restOfLine = cursor.getLineIterator()->substr(cursor.getCol()+1);
                cursor.getLineIterator()->erase(cursor.getCol()+1);
                cursor.getLineIterator()->append(toPaste.front());
                cursor.moveEndOfLine();
            }
            else {
                buffer.insert(cursor.getLineIterator()+1, toPaste.front());
                cursor.moveDown();
            }
            buffer.insert(cursor.getLineIterator()+1, toPaste.begin()+1, toPaste.end());
            cursor.moveDown(toPaste.size()-1);
            for(size_t k=1; k<quant; ++k) {
                buffer.insert(cursor.getLineIterator()+1, toPaste.begin(), toPaste.end());
                cursor.moveDown(toPaste.size());
            }
            cursor.moveEndOfLine();
            cursor.getLineIterator()->append(restOfLine);
        }

        void doTheCommand(Controller &controller) override {
            toPaste = controller.clipBoard.theClipBoard;
            shouldPasteInline = controller.clipBoard.shouldPasteInline;
            commandHelper(controller);
        }

        void undoTheCommand(Controller &controller) const override {
            size_t count = 0;
            for(size_t k=0; k<quant; ++k) {
                for(const auto &str : toPaste) count += str.size();
            }
            controller.getBuffer().delete_backward(count);
        }

        void redoTheCommand(Controller &controller) const override {
            commandHelper(controller);
        }

        public:
        PasteCommand(size_t quant): Clonable{quant}, toPaste{}, shouldPasteInline{true} {}
        PasteCommand(const PasteCommand &other): Clonable{other}, toPaste{other.toPaste} {}
        PasteCommand(PasteCommand &&other):Clonable{std::move(other)}, toPaste{std::move(other.toPaste)} {};
    };

    template<> class PasteCommand<Direction::LEFT>: public ClonableCommand<UndoableCommand, PasteCommand<Direction::LEFT>> {
        BufferType toPaste;
        bool shouldPasteInline;

        void commandHelper(Controller &controller) const {
            std::string begOfLine {""};
            PtrCursor &cursor = controller.getBuffer().ptrCursor;
            BufferType &buffer = controller.getBuffer().getBuffer();

            if(shouldPasteInline) {
                begOfLine = cursor.getLineIterator()->substr(0, cursor.getCol()+1);
                cursor.getLineIterator()->erase(0, cursor.getCol()+1);
                cursor.getLineIterator()->insert(0, toPaste.back());
                cursor.moveBeginOfLine();
            }
            else {
                buffer.insert(cursor.getLineIterator(), toPaste.back());
                cursor.moveUp();
            }
            buffer.insert(cursor.getLineIterator(), toPaste.begin(), toPaste.end()-1);
            cursor.moveUp(toPaste.size()-1);
            for(size_t k=1; k<quant; ++k) {
                buffer.insert(cursor.getLineIterator(), toPaste.begin(), toPaste.end());
                cursor.moveUp(toPaste.size());
            }
            cursor.moveBeginOfLine();
            cursor.getLineIterator()->insert(0, begOfLine);
        }

        void doTheCommand(Controller &controller) override {
            toPaste = controller.clipBoard.theClipBoard;
            shouldPasteInline = controller.clipBoard.shouldPasteInline;
            commandHelper(controller);
        }

        void undoTheCommand(Controller &controller) const override {
            size_t count = 0;
            for(size_t k=0; k<quant; ++k) {
                for(const auto &str : toPaste) count += str.size();
            }
            controller.getBuffer().delete_forward(count);
        }

        void redoTheCommand(Controller &controller) const override {
            commandHelper(controller);
        }

        public:
        PasteCommand(size_t quant): Clonable{quant}, toPaste{}, shouldPasteInline{true} {}
        PasteCommand(const PasteCommand &other): Clonable{other}, toPaste{other.toPaste} {}
        PasteCommand(PasteCommand &&other):Clonable{std::move(other)}, toPaste{std::move(other.toPaste)} {};
    };

}

#endif
