#include "component.h"

namespace VM {
    Component::Component(const Coordinates &posn, const Coordinates &size): size(size), posn(posn) {}
    Component::Component(): size{0,0}, posn{0,0} {}

    void Component::appendChildren(std::shared_ptr<Component> childrenComponent) {
        detachChildren(childrenComponent);
        children.push_back(childrenComponent);
    }

    void Component::detachChildren(std::shared_ptr<Component> childrenComponent) {
        children.remove(childrenComponent);
    }

    void Component::draw(const Coordinates &parentPosn, TextDisplay &display) {
        const Coordinates myCoordinates = parentPosn + posn;
        for(const std::shared_ptr<Component> &child : children)
            child->draw(myCoordinates, display);
    }

    const Coordinates &Component::getSize() const {
        return size;
    }

    void Component::setSize(const Coordinates &newSize) {
        size = newSize;
    }

    const Coordinates &Component::getPosn() const {
        return posn;
    }

    void Component::setPosn(const Coordinates &posn) {
        Component::posn = posn;
    }

    Component::~Component() {}
}
