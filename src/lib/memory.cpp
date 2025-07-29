//
// Created by laure on 28/07/2025.
//

#include "memory.hpp"

#include <cstring>
#include <memory>

constexpr void safe::memory::release() const {
    if (_ptr != nullptr) {
        _ptr.reset();
        _size = 0;
    }
}

safe::memory::memory(const size_t size): _ptr(nullptr), _size(0) {
    _ptr = std::make_unique<std::byte[]>(size);
    _size = size;
}

safe::memory::~memory() {
   release();
}

safe::memory::memory(const memory &other) {
    _ptr = std::make_unique<std::byte[]>(other._size);
    _size = other._size;
    std::memcpy(_ptr.get(), other._ptr.get(), _size);
}

constexpr safe::memory & safe::memory::operator=(const memory &other) {
    if (&other == this) return *this;

    release();
    
    _ptr = std::make_unique<std::byte[]>(other._size);
    _size = other._size;
    std::memcpy(_ptr.get(), other._ptr.get(), _size);
    return *this;
}

constexpr safe::memory::memory(memory &&other) noexcept {
    _ptr = std::move(other._ptr);
    _size = other._size;
    other.release();
}

constexpr safe::memory & safe::memory::operator=(memory &&other) noexcept {
    if (&other == this) return *this;
    
    _ptr = std::move(other._ptr);
    _size = other._size;
    other.release();
    
    return *this;
}
