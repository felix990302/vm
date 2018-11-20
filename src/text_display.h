#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <memory>

class Component;

namespace vm {

    class TextDisplay {
        int height, width;
        std::shared_ptr<Component> main_component:

        void put(int x, int y, char c); //TODO extend to color
        void get(int x, int y, char c);

        void redraw();
    };
}
#endif //VM_TEXT_DISPLAY_H
