//
// Created by laure on 29/07/2025.
//

#ifndef VAR_HPP
#define VAR_HPP

#include <algorithm>

namespace safe {
    template<typename T, T TDefault = T{}>
    class var {
    private:
        T _value = TDefault;
    public:
        var() = default;

        var(const T value) : _value(value) {}

        var(const var &other) : _value(other._value) {}

        var &operator=(const var &other) {
            if (this != &other) {
                _value = other._value;
            }
            return *this;
        }

        var &operator=(T value) {
            _value = value;
            return *this;
        }

        explicit var(var && other) noexcept : _value(std::move(other._value)) {}

        var &operator=(var && other) noexcept {
            if (this != &other) {
                _value = std::move(other._value);
            }
            return *this;
        }
        
        var &operator=(T && value) noexcept {
            _value = std::move(value);
            return *this;
        }

        constexpr T clone() const {
            return _value;
        }
    };
}

#endif //VAR_HPP
