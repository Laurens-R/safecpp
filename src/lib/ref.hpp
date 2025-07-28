//
// Created by laure on 29/07/2025.
//

#ifndef REF_HPP
#define REF_HPP

namespace safe {
    template<typename T>
    class ref {
        const T & _data;
    public:
        explicit ref(const T & data) : _data(data) 
        {}

        ref(const ref<T> & other) : _data(other._data){}

        ref<T> & operator=(const ref<T> & other) {
            if (this != &other) {
                const_cast<T &>(_data) = other._data; // Use const_cast to allow assignment
            }
            return *this;
        }
        
        explicit operator T() const {
            return _data;
        }

        explicit operator const T &() const {
            return _data;
        }
    };
}

#endif //REF_HPP
