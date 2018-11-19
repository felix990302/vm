#ifndef LINES_H
#define LINES_H

#include <cstddef>
#include <iostream>


namespace VM {
    template<typename T, typename U> class BufferBase {
        typedef T LineContainer;
        typedef U CharContainer;

        LineContainer theBuffer;

        public:
        BufferBase(std::istream &in): theBuffer{} {
            std::string tempStr;
            while(std::getline(in, tempStr)) {
               CharContainer temp;
               for(auto &v : tempStr) temp.push_back(std::move(v));
               theBuffer.push_back(std::move(temp));
            }
        }
    };
}

#endif
