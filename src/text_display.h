#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <memory>
#include <string>

#include "coordinates.h"
class Component;


namespace VM {

    class TextDisplay {
    private:
        std::shared_ptr<Component> main_component:

    public:
        void putc(const Coordinates &c, char c); //TODO extend to color
        void puts(const Coordinates &c, const std::string &s);
        //char get(int x, int y, char c);
        void redraw();

    public:

    };
}
#endif
