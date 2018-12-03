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
        virtual void putc(const Coordinates &c, char ch) = 0;
        virtual void puts(const Coordinates &c, const std::string &s) =0;
        virtual void flush(const Coordinates &c) = 0; // flushes to end of line

        virtual void redraw();
        virtual void resizeHandler(const Coordinates &size);
        virtual void setCursorPosition(size_t y, size_t x) = 0;


        const std::shared_ptr<Component> &getMainComponent() const;

        void setMainComponent(const std::shared_ptr<Component> &mainComponent);

        virtual ~TextDisplay() = 0;
    };
}
#endif
