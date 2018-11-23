#ifndef MODE_H
#define MODE_H


namespace VM {
    class Controller;

    class Mode {
        public:
        virtual void processChar(char c, Controller &controller) = 0;
    };
}

#endif
