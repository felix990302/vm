#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "component.h"

namespace VM {

    class Controller;
    class FileBuffer;

    class StatusBar : public Component {
        FileBuffer *fileBuffer;
        Controller *controller;
    public:
        StatusBar(FileBuffer *, Controller *);
        void draw(const Coordinates &parentPosn, TextDisplay &display) override;
    };

}


#endif
