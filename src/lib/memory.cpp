//
// Created by laure on 28/07/2025.
//

#include "memory.hpp"

#include <cstring>
#include <memory>

void safe::memory::release() const {
    if (_ptr != nullptr) {
        std::free(_ptr);
        _ptr = nullptr;
        _size = 0;
    }
}

safe::memory::memory(size_t size): _ptr(nullptr), _size(0) {
    _ptr = static_cast<std::byte*>(std::malloc(size));
    _size = size;
}

safe::memory::~memory() {
   release();
}

safe::memory::memory(const memory &other) {
    _ptr = static_cast<std::byte*>(std::malloc(other._size));
    _size = other._size;
    std::memcpy(_ptr, other._ptr, _size);
}

safe::memory & safe::memory::operator=(const memory &other) {
    if (&other == this) return *this;

    release();
    
    _ptr = static_cast<std::byte*>(std::malloc(other._size));
    _size = other._size;
    std::memcpy(_ptr, other._ptr, _size);
    return *this;
}

safe::memory::memory(memory &&other) noexcept {
    _ptr = other._ptr;
    _size = other._size;
    other.release();
}

safe::memory & safe::memory::operator=(memory &&other) noexcept {
    if (&other == this) return *this;
    
    _ptr = other._ptr;
    _size = other._size;
    other.release();
    
    return *this;
}
