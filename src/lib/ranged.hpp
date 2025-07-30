/*
    MIT License

    Copyright (c) 2025 Laurens Ruijtenberg

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/


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
        ranged(T value = TDefault) : _value(value) {
            if (value < TFrom || value > TTo) {
                throw std::out_of_range("Value is out of range");
            }
        }
        
        ranged(const ranged<T, TFrom, TTo> &other) : _value(other._data) {
            //no additional checks needed, as the value is already validated
        }
        
        [[nodiscard]] constexpr ranged& operator=(const ranged<T, TFrom, TTo> &other) {
            if (this != &other) {
                  _value = other._data;
            }
            return *this;
        }

        template<T TFromOther, T TToOther>
        explicit ranged(const ranged<T, TFromOther, TToOther> &other) : _value(other.value()) {
            if (other.value() < TFrom || other.value() > TTo) {
                throw std::out_of_range("Value is out of range");
            }
        }
        
        template<T TFromOther, T TToOther>
        [[nodiscard]] constexpr ranged& operator=(const ranged<T, TFromOther, TToOther> &other) {
            if (this != &other) {
                if (_value < TFrom || _value > TTo) {
                    throw std::out_of_range("Value is out of range");
                }
                
                _value = other.value();
            }
            return *this;
        }

        //this is allowed in this case because we are dealing with numerical values only.
        [[nodiscard]] operator const T() const {
            return _value;
        }

        [[nodiscard]] constexpr bool operator==(const ranged<T, TFrom, TTo> &other) const {
            return _value == other._data;
        }

        [[nodiscard]] constexpr bool operator!=(const ranged<T, TFrom, TTo> &other) const {
            return !(*this == other);
        }
    };
}

#endif //RANGE_HPP
