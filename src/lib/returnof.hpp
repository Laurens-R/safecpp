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


#ifndef RETURNOF_HPP
#define RETURNOF_HPP

#include <type_traits>

#include "owner.hpp"

namespace safe {
    template<typename T>
    class return_of {
        static_assert(!std::is_reference_v<T>, "Returning references are considered unsafe, unless provided back through a ref class object.");
        static_assert(!std::is_pointer_v<T>, "Returning pointers is considered unsafe, unless provided back through a ptr class object.");
        static_assert(!std::is_void_v<T>, "Returning void is not allowed, just use void to indicate no return value.");
        T _value;
    public:
        constexpr return_of(const T &value) : _value(value) {}
        constexpr return_of(T &&value) noexcept : _value(std::move(value)) {}

        return_of(const return_of<T> &other) = delete;
        return_of(return_of<T> &&other) noexcept = delete;

        constexpr return_of &operator=(const T &value) {
            _value = value;
            return *this;
        }
 
        constexpr return_of &operator=(T &&value) noexcept {
            _value = std::move(value);
            return *this;
        }

        [[nodiscard]] constexpr operator owner<T>() const {
            static_assert(!std::is_same_v<T, safe::ref<T>> && !std::is_same_v<T, safe::mut<T>>, "This return value contains either a reference or mutable reference. As such ownership cannot be transferred over.");
            return _value;
        }

        [[nodiscard]] constexpr operator ref<T>() const {
            return safe::ref<T>::create_from(_value);;
        }

        [[nodiscard]] constexpr operator mut<T>() const {
            return safe::mut<T>::create_from(_value);;
        }

        [[nodiscard]] constexpr owner<T> owner() const requires (!std::is_same_v<T, safe::ref<T>> && !std::is_same_v<T, safe::mut<T>>) {
            static_assert(!std::is_same_v<T, safe::ref<T>> && !std::is_same_v<T, safe::mut<T>>, "This return value contains either a reference or mutable reference. As such ownership cannot be transferred over.");
            return _value;
        }

        [[nodiscard]] constexpr ref<T> ref() {
            return safe::ref<T>::create_from(_value);
        }

        [[nodiscard]] constexpr mut<T> mut() {
            return safe::mut<T>::create_from(_value);
        }

        [[nodiscard]] constexpr T value() {
            return _value;
        }

        [[nodiscard]] T unsafe_get() const {
            return _value;
        }
    };
}


#endif //RETURNOF_HPP
