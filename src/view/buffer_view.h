#ifndef BUFFER_VIEW_H
#define BUFFER_VIEW_H

#include "model/cursor.h"
#include "component.h"


namespace VM {

    class FileBuffer;

    class BufferView : public Component {
    private:
        Cursor cursor;
        FileBuffer *fileBuffer;
        bool showLinesNumbers = false;
    public:

        BufferView (FileBuffer * fileBuffer);
        void draw(const Coordinates &parentPosn, TextDisplay &display) override;
        void setLineNumbers(bool onOrOf) {showLinesNumbers = onOrOf;}
    };
}

#endif

