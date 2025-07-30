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


#ifndef OWNER_HPP
#define OWNER_HPP

#include "mut.hpp"
#include "ref.hpp"

#include "common_operators.hpp"

namespace safe {
    
    template<typename T> //the added operators are included through 'deduce this' classes (effectively using a decorator type pattern)
    class owner
        : public common_operators<T>, common_operators_unmutable<T>
    {
    protected:
        T _data;
    public:
        constexpr owner() : _data(T{}) {}

        // Add this constructor
        template<typename... Args>
        constexpr explicit owner(Args&&... args) 
            : common_operators<T>(),
              common_operators_unmutable<T>(),
              _data(std::forward<Args>(args)...)
        {}
        
        constexpr owner(const T & data) : _data(data) {}

        constexpr owner<T> & operator=(const T & data) {
            _data = data; // Direct assignment
            return *this;
        }

        constexpr owner(const owner<T> & other) : _data(other._data) {}

        constexpr owner(owner<T> && other) noexcept : _data(std::move(other._data)) {}
               
        [[nodiscard]] constexpr operator ref<T>() const {
            return _data;
        }

        [[nodiscard]] constexpr operator mut<T>() const {
            return _data;
        }

        [[nodiscard]]  constexpr ref<T> ref() {
            static_assert(std::is_same_v<T, safe::ref<T>>, "The return value is not a safe reference.");
            return _data;
        }

        [[nodiscard]] constexpr mut<T> mut() {
            static_assert(std::is_same_v<T, safe::mut<T>>, "The return value is not a safe mutable reference.");
            return _data;
        }
        
        [[nodiscard]] constexpr T value() const {
            return _data;
        }

        [[nodiscard]] constexpr T clone() const {
            return _data;
        }

        [[nodiscard]] const T & unsafe_reference() const {
            return _data;
        }
    };

    
}

#endif //OWNER_HPP
