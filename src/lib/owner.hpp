//
// Created by laure on 29/07/2025.
//

#ifndef OWNER_HPP
#define OWNER_HPP

#include "mut.hpp"
#include "ref.hpp"

#include "common_operators.hpp"

namespace safe {
    
    template<typename T, T TDefault = T{}> //the added operators are included through 'deduce this' classes (effectively using a decorator type pattern)
    class owner : public common_operators<T>, common_operators_unmutable<T> {
    protected:
        T _data;
        ref<T> _readonly_ref;
        mut<T> _mutable_ref;
    public:
        owner() : _data(TDefault), _readonly_ref(_data), _mutable_ref(_data) {}
        
        owner(const T & data) : _data(data), _readonly_ref(_data), _mutable_ref(_data) {}

        owner(const owner<T> & other) : _data(other._data) {}

        owner(owner<T> && other) noexcept : _data(std::move(other._data)) {}
        
        operator T() const {
            return _data;
        }
        
        constexpr operator const ref<T> & () const {
            return _readonly_ref;
        }
        
        constexpr operator mut<T>& () const {
            return _mutable_ref;;
        }        
    };

    
}

#endif //OWNER_HPP
