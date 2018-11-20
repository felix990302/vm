#ifndef BUFFER_BASE_H
#define BUFFER_BASE_H

#include <list>

namespace VM {
    typedef std::list<char> LineType;
    typedef std::list<LineType> BufferType;
}

#endif

