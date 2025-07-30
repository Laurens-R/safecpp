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
        constexpr mut(T & data) : _data(data) {}

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
        
        constexpr mut<T> & operator=(T && other) noexcept {
            if (this != &other) {
                _data = std::move(other); // Move assignment
            }
            return *this;
        }

        constexpr const T* operator->() const {
            return &_data;
        }

        [[nodiscard]] constexpr T value () const {
            return _data;
        }
        
        [[nodiscard]] constexpr T clone() const {
            return _data;
        }

        [[no_discard]] constexpr T & unsafe_reference() const {
            return _data;
        }  
    };
}
#endif //MUTABLE_H
