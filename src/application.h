#ifndef APPLICATION_H
#define APPLICATION_H

namespace VM {

    class Application {
    private:
        int argc;
        char *argv[];
    public:
        Application(int argc, char *argv[]);
        void run();
    };

}


#endif
