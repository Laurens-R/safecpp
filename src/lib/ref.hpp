//
// Created by laure on 29/07/2025.
//

#ifndef REF_HPP
#define REF_HPP

#include "common_operators.hpp"

namespace safe {
    template<typename T> //the added operators are included through 'deduce this' classes (effectively using a decorator type pattern)
    class ref : public common_operators_unmutable<T>  {
    protected:
        const T & _data;
    public:
        ref() = delete;
        explicit constexpr ref(const T & data) : _data(data) {}        
        
        ref(const ref<T> & other) = delete;
        ref(ref<T> && other) noexcept = delete;
        ref<T> & operator=(const ref<T> & other) = delete;
        ref<T> & operator=(ref<T> && other) noexcept = delete;

        const T* operator->() const {
            return &_data;
        }
        
        [[nodiscard]] constexpr T clone() const {
            return _data;
        }

        [[nodiscard]] constexpr const T & unsafe_get() const {
            return _data;
        }        
    };
}

#endif //REF_HPP
