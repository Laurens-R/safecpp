//
// Created by laure on 29/07/2025.
//

#ifndef MUT_H
#define MUT_H

#include <algorithm>

namespace safe {
    template <typename T>
    class mut {
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
        
        [[nodiscard]] constexpr operator T() const {
            return _data;
        }

    };
}
#endif //MUTABLE_H
