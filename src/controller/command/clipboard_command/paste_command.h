#ifndef PASTE_COMMAND_H
#define PASTE_COMMAND_H

#include "model/file_buffer.h"
#include "controller/controller.h"
#include "controller/command/undoable_command.h"
#include "controller/command/motion/direction.h"


namespace VM {
    class PasteCommand;



    class PasteCommand: public ClonableCommand<UndoableCommand, PasteCommand> {
        LineType toPaste;
        bool multiline;
        bool pasteAfter;
        Cursor pasteStarts;


        Cursor commandHelper(Controller &controller) const{
            PtrCursor &cursor = controller.getBuffer().ptrCursor;
            FileBuffer &buffer = controller.getBuffer();
            cursor.setType(PtrCursor::CursorMovement::IteratorCursor);
            Cursor pasteStarts{0,0};
            if(multiline) {
                if(pasteAfter)
                {
                    cursor.moveDown();
                    if(cursor.isEOF()) buffer.type("\n");
                }
                cursor.moveBeginOfLine();
                pasteStarts = cursor.getCursor();
                for(size_t k = 0; k < quant; ++k) buffer.type(toPaste);
                if(cursor.isEOF()) buffer.delete_backward(1);
                cursor.setCursor(pasteStarts);
            }
            else {
                if(pasteAfter) cursor.moveRight();
                pasteStarts = cursor.getCursor();
                for(size_t k = 0; k < quant; ++k) buffer.type(toPaste);
                cursor.moveLeft();
            }
            return pasteStarts;
        }

        void doTheCommand(Controller &controller) override {
            toPaste = controller.clipBoard.theClipBoard;
            multiline = controller.clipBoard.multiLine;
            pasteStarts = commandHelper(controller);
        }

        void undoTheCommand(Controller &controller) const override {
            controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
            controller.getBuffer().ptrCursor.setCursor(pasteStarts);
            controller.getBuffer().delete_forward(quant * toPaste.size());
            controller.getBuffer().ptrCursor.setCursor(startPosn);
        }

        void redoTheCommand(Controller &controller) const override {
            commandHelper(controller);
        }

        public:
        PasteCommand(size_t quant, bool pasteAfter): Clonable{quant}, toPaste{}, multiline{false}, pasteAfter{pasteAfter}, pasteStarts{0,0} {}
        PasteCommand(const PasteCommand &other): Clonable{other}, toPaste{other.toPaste}, multiline{other.multiline}, pasteAfter{other.pasteAfter}, pasteStarts{0,0}{}
        PasteCommand(PasteCommand &&other):Clonable{std::move(other)}, toPaste{std::move(other.toPaste)}, multiline{other.multiline}, pasteStarts{0,0} {};
    };



}

#endif
