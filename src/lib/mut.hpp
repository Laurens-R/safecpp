//
// Created by laure on 29/07/2025.
//

#ifndef MUT_H
#define MUT_H

#include <algorithm>

#include "common_operators.hpp"

namespace safe {
    template <typename T> //the added operators are included through 'deduce this' classes (effectively using a decorator type pattern)
    class mut : public common_operators<T>, common_operators_unmutable<T> {
    private:
        T& _data;
    public:
        explicit constexpr mut(T & data) : _data(data) {}

        mut(const mut<T> & other) = delete;
        mut<T> & operator=(const mut<T> & other) = delete;
        mut<T> & operator=(mut<T> && other) = delete;
        mut(mut<T> && other) noexcept = delete;
        
        constexpr mut<T> & operator=(const T & other) {
            if (this != &other) {
                _data = other; // Direct assignment
            }
            return *this;
        }
        
        mut<T> & operator=(T && other) noexcept {
            if (this != &other) {
                _data = std::move(other); // Move assignment
            }
            return *this;
        }

        const T* operator->() const {
            return &_data;
        }
        
        [[nodiscard]] T clone() const {
            return _data;
        }

        [[nodiscar]] T & unsafe_get() const {
            return _data;
        }
    };
}
#endif //MUTABLE_H
