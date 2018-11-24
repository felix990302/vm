#ifndef COMPONENT_H
#define COMPONENT_H

#include <list>
#include <memory>
#include "coordinates.h"
#include "text_display.h"

namespace VM {
    class Component {
        Coordinates size, posn;
    public:
        const Coordinates &getSize() const;

        virtual void setSize(const Coordinates &size);

        const Coordinates &getPosn() const;

        virtual void setPosn(const Coordinates &posn);

        void enforceFitIntoSize(const Coordinates &size);

    private:
        std::list<std::shared_ptr<Component> > children;

    public:
        Component(const Coordinates &posn, const Coordinates &size);
        Component();

        //Component(const Component &component) = delete;
        //Component(Component &&component) = delete;
        //Component & operator=(const Component &component) = delete;
        //Component & operator=(Component &&component) = delete;
        //~Component();

        void appendChildren(std::shared_ptr<Component> childrenComponent);
        void detachChildren(std::shared_ptr<Component> childrenComponent);

        virtual void draw(const Coordinates &parentPosn, TextDisplay &display);
    };
}

#endif //VM_COMPONENT_H
