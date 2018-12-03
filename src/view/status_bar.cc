#include "controller/mode/mode.h"
#include "controller/controller.h"
#include "status_bar.h"
#include <string>
#include <iomanip>
#include "model/file_buffer.h"


namespace VM {
    StatusBar::StatusBar(VM::FileBuffer *fileBuffer, VM::Controller *controller, BufferView *bufferView): fileBuffer{fileBuffer}, controller {controller}, bufferView{bufferView}  {}

    void StatusBar::draw(const VM::Coordinates &parentPosn, VM::TextDisplay &display) {
        if(getSize().y < 1)
            return;

        display.flush(parentPosn + getPosn());
        std::string left = controller->getMode().getStatusBarLeft();
        std::string right = controller->getMode().getStatusBarRight();
        std::string coordinates = std::to_string(fileBuffer->ptrCursor.getLine()+1)
                + "," + std::to_string(fileBuffer->ptrCursor.getCol()+1);
        std::stringstream ss;
        ss << left << std::setw(getSize().x-left.size())<< std::right << (right + "    " + coordinates + "  " +  bufferView->getLinePercantage());
        std::string output = ss.str();
        display.puts(parentPosn + getPosn(),output);
    }

    bool StatusBar::setCursor(const Coordinates &parentPosn, TextDisplay &display) {
            int cur = controller->getMode().getStatusBarCursor();
            if(cur == -1)
                return false;
            display.setCursorPosition(parentPosn.y + getPosn().y, getPosn().x + parentPosn.x + cur + 1);
            return true;
    }
}
