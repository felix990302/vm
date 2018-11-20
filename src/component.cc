#include "component.h"

namespace VM {
    Component::Component(const Coordinates &posn, const Coordinates &size):  posn(posn), size(size) {}

    void Component::appendChildren(std::shared_ptr<Component> childrenComponent) {
        detachChildren(childrenComponent);
        children.push_back(childrenComponent);
    }

    void Component::detachChildren(std::shared_ptr<Component> childrenComponent) {
        children.remove(childrenComponent);
    }

    void Component::draw(const Coordinates &parentPosn, const TextDisplay &display) {
        const Coordinates myCoordinates = parentPosn + posn;
        for(const Component & child : children)
            child.draw(myCoordinates);
    }

    const Coordinates &Component::getSize() const {
        return size;
    }

    void Component::setSize(const Coordinates &size) {
        if(size == newSize) return;
        size = newSize;
    }

    const Coordinates &Component::getPosn() const {
        return posn;
    }

    void Component::setPosn(const Coordinates &posn) {
        Component::posn = posn;
    }


}