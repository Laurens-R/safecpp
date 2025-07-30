//
// Created by laure on 29/07/2025.
//

#ifndef RANGE_HPP
#define RANGE_HPP

#include <stdexcept>
#include <type_traits>

#include "common_operators.hpp"

namespace safe {
    template<typename T, T TFrom, T TTo, T TDefault = T{}>
    class ranged : public common_operators_unmutable<T> {
        static_assert(TDefault >= TFrom && TDefault <= TTo, "TDefault must be within the range [TFrom, TTo]");
        static_assert(std::is_arithmetic_v<T>, "Type T must be an arithmetic type (integral or floating point)");
        static_assert(TFrom < TTo, "TFrom must be less than TTo");
        
        T _value;
    
    public:
        constexpr ranged(T value = TDefault) : _value(value) {
            if (value < TFrom || value > TTo) {
                throw std::out_of_range("Value is out of range");
            }
        }
        
        constexpr ranged(const ranged<T, TFrom, TTo> &other) : _value(other._value) {
            //no additional checks needed, as the value is already validated
        }
        
        constexpr ranged& operator=(const ranged<T, TFrom, TTo> &other) {
            if (this != &other) {
                  _value = other._value;
            }
            return *this;
        }

        template<T TFromOther, T TToOther>
        constexpr explicit ranged(const ranged<T, TFromOther, TToOther> &other) : _value(other.value()) {
            if (other.value() < TFrom || other.value() > TTo) {
                throw std::out_of_range("Value is out of range");
            }
        }
        
        template<T TFromOther, T TToOther>
        constexpr ranged& operator=(const ranged<T, TFromOther, TToOther> &other) {
            if (this != &other) {
                if (_value < TFrom || _value > TTo) {
                    throw std::out_of_range("Value is out of range");
                }
                
                _value = other.value();
            }
            return *this;
        }
        
        operator const T() const {
            return _value;
        }

        constexpr bool operator==(const ranged<T, TFrom, TTo> &other) const {
            return _value == other._value;
        }

        constexpr bool operator!=(const ranged<T, TFrom, TTo> &other) const {
            return !(*this == other);
        }
    };
}

#endif //RANGE_HPP
