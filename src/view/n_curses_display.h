#ifndef NCURSESDISPLAY_H
#define NCURSESDISPLAY_H

#include "text_display.h"
#include <ncurses.h>

namespace VM {

    class NCursesDisplay : public TextDisplay {
    private:
        static std::unique_ptr<NCursesDisplay> mainDisplay;
    public:
        static NCursesDisplay &getMainDisplay();

    public:
        NCursesDisplay();

        void putc(const Coordinates &c, char ch) override;

        void puts(const Coordinates &c, const std::string &s) override;

        void redraw() override;

        static void resizeHandler(int);


    };

}


#endif
