#ifndef NCURSESDISPLAY_H
#define NCURSESDISPLAY_H

#include "text_display.h"
#include <ncurses.h>

namespace VM {
    class NCursesDisplay : public TextDisplay {
    public:
        static NCursesDisplay &getMainDisplay();

        NCursesDisplay();
        NCursesDisplay(const NCursesDisplay& other) = delete;
        NCursesDisplay &operator=(const NCursesDisplay &other) = delete;

        void putc(const Coordinates &c, char ch) override;

        void puts(const Coordinates &c, const std::string &s) override;

        void redraw() override;

        static void resizeHandler(int);

        ~NCursesDisplay();
    };
}

#endif
