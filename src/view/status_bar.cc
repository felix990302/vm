#include "controller/mode/mode.h"
#include "controller/controller.h"
#include "status_bar.h"
#include <string>
#include <iomanip>
#include "model/file_buffer.h"


namespace VM {
    StatusBar::StatusBar(VM::FileBuffer *fileBuffer, VM::Controller *controller): fileBuffer{fileBuffer}, controller {controller}  {}

    void StatusBar::draw(const VM::Coordinates &parentPosn, VM::TextDisplay &display) {
        if(getSize().y < 1)
            return;

        display.flush(parentPosn + getPosn());
        std::string left = controller->getMode().getStatusBarLeft();
        std::string right = controller->getMode().getStatusBarRight();
        std::string coordinates = std::to_string(fileBuffer->ptrCursor.getLine())
                + "," + std::to_string(fileBuffer->ptrCursor.getCol());
        std::stringstream ss;
        ss << left << std::setw(getSize().x-left.size())<< std::right << (right + "    " + coordinates  + "\t");
        std::string output = ss.str();
        display.puts(parentPosn + getPosn(),output);
        //TODO : make it nicer
    }
}
