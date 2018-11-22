#ifndef MODE_H
#define MODE_H


namespace VM {
    class FileBuffer;

    class Mode {
        public:
        virtual void processChar(char c, FileBuffer &fileBuffer) = 0;
    };
}

#endif
