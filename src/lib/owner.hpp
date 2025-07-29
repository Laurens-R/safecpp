//
// Created by laure on 29/07/2025.
//

#ifndef OWNER_HPP
#define OWNER_HPP

#include "mutable_ref.hpp"
#include "readonly_ref.hpp"
#include "ref_counter.hpp"

namespace safe {
    template<typename T>
    class owner {
    private:
        T _data;
        readonly_ref<T> _readonly_ref;
        mutable_ref<T> _mutable_ref;
        
    public:

        owner(const T & data) : _data(data), _readonly_ref(_data), _mutable_ref(_data) {}

        owner(const owner<T> & other) : _data(other._data) {}

        owner(owner<T> && other) noexcept : _data(std::move(other._data)) {}
        
        explicit operator T() const {
            return _data;
        }
        
        operator readonly_ref<T> & () const {
            return _readonly_ref;
        }

        operator mutable_ref<T>& () const {
            return _mutable_ref;;
        }        
    };
}

#endif //OWNER_HPP
