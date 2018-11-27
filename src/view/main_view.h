#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "component.h"

namespace VM {

    class BufferView;
    class StatusBar;
    class FileBuffer;
    class Controller;

    class MainView : public Component {
        std::shared_ptr<BufferView> bufferView;
        std::shared_ptr<StatusBar> statusBar;

    public:
        MainView(FileBuffer *fileBuffer, Controller *controller);
        void setSize(const Coordinates &size) override;
    };

}


#endif
