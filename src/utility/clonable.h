#ifndef CLONABLE_H
#define CLONABLE_H

#include <memory>


namespace VM {
    template<typename AbstractBase, typename Base, typename Sub> class Clonable: public Base {
        public:
        std::unique_ptr<AbstractBase> clone() const override final {
            return std::make_unique<Sub>(static_cast<const Sub &>(*this));
        }

        template<typename ...Args> Clonable(Args &&...args): Base{std::forward<Args>(args)...} {}
    };
}

#endif
