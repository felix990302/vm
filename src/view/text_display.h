#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <memory>
#include <string>


#include "coordinates.h"




namespace VM {

    class Component;

    class TextDisplay {
    private:
        std::shared_ptr<Component> mainComponent;
    public:


        TextDisplay();
        virtual void putc(const Coordinates &c, char ch) = 0; //TODO extend to color
        virtual void puts(const Coordinates &c, const std::string &s) =0;

        virtual void redraw();
        virtual void resizeHandler(const Coordinates &size);


        const std::shared_ptr<Component> &getMainComponent() const;

        void setMainComponent(const std::shared_ptr<Component> &mainComponent);


    };
}
#endif
