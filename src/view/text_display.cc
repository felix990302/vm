#include "text_display.h"
#include "component.h"

namespace VM {
    void TextDisplay::redraw() {
        mainComponent->draw(Coordinates {0,0}, *this);
    }

    void TextDisplay::resizeHandler(const Coordinates &size) {
        mainComponent->setSize(size);
        redraw();
    }

    const std::shared_ptr<Component> &TextDisplay::getMainComponent() const {
        return mainComponent;
    }

    void TextDisplay::setMainComponent(const std::shared_ptr<Component> &mainComponent) {
        TextDisplay::mainComponent = mainComponent;
        redraw();
    }

    TextDisplay::~TextDisplay() {}
}
