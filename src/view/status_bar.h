#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "component.h"
#include "buffer_view.h"

namespace VM {

    class Controller;
    class FileBuffer;

    class StatusBar : public Component {
        FileBuffer *fileBuffer;
        Controller *controller;
        BufferView *bufferView;
    public:
        StatusBar(FileBuffer *, Controller *, BufferView *);
        void draw(const Coordinates &parentPosn, TextDisplay &display) override;
        bool setCursor(const Coordinates &parentPosn, TextDisplay &display);
    };


}


#endif
