#ifndef CURSOR_H
#define CURSOR_H

#include <cstddef>
#include <utility>


namespace VM {
    template<typename T, typename U> class Cursor {
        typedef T lineMarker;
        typedef U charMarker;
        typedef std::pair<lineMarker, charMarker> position;

        position posn;

        public:
        Cursor(const lineMarker &linePosn, const charMarker &charPosn):
            posn{linePosn, charPosn}
        {}
        const position &getPosn() const {return posn;}
        const lineMarker &setLinePosn() const {return posn.first;}
        const charMarker & getCharPosn() const {return posn.second;}
        void setLinePosn(const lineMarker &newLinePosn) {posn.first = newLinePosn;}
        void setCharPosn(const charMarker &newCharPosn) {posn.second = newCharPosn;}
        void setPosn(const size_t &newLinePosn, const size_t &newCharPosn) {
            setLinePosn(newLinePosn);
            setCharPosn(newCharPosn);
        }
    };
}

#endif
