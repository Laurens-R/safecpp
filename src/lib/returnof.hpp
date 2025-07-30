//
// Created by laure on 30/07/2025.
//

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
        return_of(const T &value) : _value(value) {}
        return_of(T &&value) noexcept : _value(std::move(value)) {}

        return_of(const return_of<T> &other) = delete;
        return_of(return_of<T> &&other) noexcept = delete;

        return_of &operator=(const T &value) {
            _value = value;
            return *this;
        }
 
        return_of &operator=(T &&value) noexcept {
            _value = std::move(value);
            return *this;
        }

        operator owner<T>() const {
            static_assert(!std::is_same_v<T, safe::ref<T>> && !std::is_same_v<T, safe::mut<T>>, "This return value contains either a reference or mutable reference. As such ownership cannot be transferred over.");
            return _value;
        }

        operator ref<T>() const {
            static_assert(std::is_same_v<T, safe::ref<T>>, "The return value is not a safe reference.");
            return _value;
        }

        operator mut<T>() const {
            static_assert(std::is_same_v<T, safe::mut<T>>, "The return value is not a mutable reference.");
            return _value;
        }

        owner<T> as_owner() const requires (!std::is_same_v<T, safe::ref<T>> && !std::is_same_v<T, safe::mut<T>>) {
            static_assert(!std::is_same_v<T, safe::ref<T>> && !std::is_same_v<T, safe::mut<T>>, "This return value contains either a reference or mutable reference. As such ownership cannot be transferred over.");
            return _value;
        }

        ref<T> as_ref() {
            static_assert(std::is_same_v<T, safe::ref<T>>, "The return value is not a safe reference.");
            return _value;
        }

        mut<T> as_mut() {
            static_assert(std::is_same_v<T, safe::mut<T>>, "The return value is not a safe mutable reference.");
            return _value;
        }

        T as_value() {
            return _value;
        }

        [[nodiscard]] T unsafe_get() const {
            return _value;
        }
    };
}


#endif //RETURNOF_HPP
