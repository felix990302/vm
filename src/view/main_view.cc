#include "main_view.h"
#include "buffer_view.h"
#include "status_bar.h"

namespace VM {

    void MainView::setSize(const Coordinates &size) {
        Component::setSize(size);
        if(getSize().y < 2 ) return;
        bufferView->setSize(getSize() - Coordinates {0, 1});
        statusBar->setSize(Coordinates{getSize().x ,1});
        bufferView->setPosn(Coordinates {0,0});
        statusBar->setPosn(Coordinates {0, getSize().y - 1});
    }

    MainView::MainView(FileBuffer *fileBuffer, Controller *controller) :
        bufferView {std::make_shared<BufferView>(fileBuffer)},
        statusBar {std::make_shared<StatusBar>(fileBuffer, controller)} {
            appendChildren(statusBar);
            appendChildren(bufferView);
    }

    void MainView::draw(const Coordinates &parentPosn, TextDisplay &display) {
        Component::draw(parentPosn, display);
        if(!statusBar->setCursor(parentPosn, display))
            bufferView->setCursor(parentPosn, display);
    }


}