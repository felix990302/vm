#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <memory>
#include "coordinates.h"
#include "text_display.h"

namespace VM {
    class Component{
        Coordinates size, posn;
        std::vector<std::shared_ptr<Component> > children;

    public:
        Component(const Coordinates &posn, const Coordinates &size);

        //Component(const Component &component) = delete;
        //Component(const Component &&component) = delete;
        //Component & operator=(const Component &component) = delete;
        //Component & operator=(const Component &&component) = delete;
        //~Component();

        void appendChildren(std::shared_ptr<Component> childrenComponent);
        void detachChildren(std::shared_ptr<Component> childrenComponent);

        virtual void draw(const Coordinates &parentPosn, const TextDisplay &display);

        virtual void resize(const Coordinates &newSize);
        virtual void move(const Coordinates &newPos);
    };
}

#endif //VM_COMPONENT_H
