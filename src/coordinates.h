#ifndef COORDINATES_H
#define COORDINATES_H


#include <cstddef>

namespace VM {

    typedef size_t cor_t;

    struct Coordinates {
        cor_t x, y;
        Coordinates operator +(const Coordinates &b) const
        {
            return Coordinates{x+b.x, y+b.y};
        }
    };

}


#endif
