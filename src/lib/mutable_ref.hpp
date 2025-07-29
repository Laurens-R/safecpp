//
// Created by laure on 29/07/2025.
//

#ifndef MUTABLE_H
#define MUTABLE_H

#include <algorithm>

namespace safe {
    template <typename T>
    class mutable_ref {
    private:
        T& _data;
    public:
        explicit mutable_ref(T & data) : _data(data) {}

        mutable_ref(const mutable_ref<T> & other) = delete;
        mutable_ref<T> & operator=(const mutable_ref<T> & other) = delete;
        mutable_ref<T> & operator=(mutable_ref<T> && other) = delete;
        mutable_ref(mutable_ref<T> && other) noexcept = delete;
        
        operator T() const {
            return _data;
        }

        mutable_ref<T> & operator=(const T & other) {
            if (this != &other) {
                _data = other; // Direct assignment
            }
            return *this;
        }
        
        mutable_ref<T> & operator=(T && other) {
            if (this != &other) {
                _data = std::move(other); // Move assignment
            }
            return *this;
        }
    };
}
#endif //MUTABLE_H
