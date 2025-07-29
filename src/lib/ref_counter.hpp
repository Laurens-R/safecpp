//
// Created by laure on 29/07/2025.
//

#ifndef REF_COUNTER_HPP
#define REF_COUNTER_HPP

#include "assert.hpp"
namespace safe {
    class ref_counter {
    private:
        size_t counter = 0;
    public:
        ref_counter() = default;
    
        ~ref_counter() {
            safe_assert(counter != 0, "Reference counter is not zero at destruction");
        }
    
        void increment() {
            ++counter;
        }
        void release() {
            --counter;
        }
    };
}

#endif //REF_COUNTER_HPP
