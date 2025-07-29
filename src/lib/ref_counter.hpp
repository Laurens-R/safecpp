//
// Created by laure on 29/07/2025.
//

#ifndef REF_COUNTER_HPP
#define REF_COUNTER_HPP
#include <stdexcept>

class ref_counter {
private:
    size_t counter = 0;
public:
    ref_counter() = default;
    
    ~ref_counter() {
        if (counter != 0) {
            throw std::runtime_error("Reference counter is not zero at destruction");
        }
    }
    
    increment() {
        ++counter;
    }
    release() {
        --counter;
    }
};

#endif //REF_COUNTER_HPP
