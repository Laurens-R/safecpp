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

#ifndef MEMORY_H
#define MEMORY_H

#include <memory>
#include <span>
#include <stdexcept>
#include <type_traits>

#include "returnof.hpp"

namespace safe {

    /**
     * A memory class that provides a safe way to manage raw memory.
     * It allows for reading and writing fundamental types and PODs
     * while ensuring that accesses are within bounds. It's meant
     * as a safer alternative to void pointers.
     */
    class memory {
    public:
        template<typename T>
        constexpr bool is_safe_index(const size_t offset) const {
            return (offset + sizeof(T)) < _size;
        }
    private:
        mutable std::unique_ptr<std::byte[]> _ptr = nullptr;
        mutable size_t _size = 0;

        template<typename T>
        constexpr T * get_pointer(const size_t offset) const {
            /* The goal of this method is to do branchless bounds checks */
            const uintptr_t mask = ((offset + sizeof(T)) < _size);
            auto base = reinterpret_cast<uintptr_t>(_ptr.get() + offset);
            return reinterpret_cast<T *>(base * mask);
        }

        constexpr void release() const {
            if (_ptr != nullptr) {
                _ptr.reset();
                _size = 0;
            }
        }
        
    public:
        /**
         * Initializes a memory block with the given size.
         * @param size The size of the memory block to allocate in bytes.
         */
        memory(const size_t size): _ptr(nullptr), _size(0) {
            _ptr = std::make_unique<std::byte[]>(size);
            _size = size;
        }

        ~memory() {
            release();
        }

        memory(const memory &other) {
            _ptr = std::make_unique<std::byte[]>(other._size);
            _size = other._size;
            std::memcpy(_ptr.get(), other._ptr.get(), _size);
        }

        constexpr safe::memory & operator=(const memory &other) {
            if (&other == this) return *this;

            release();
    
            _ptr = std::make_unique<std::byte[]>(other._size);
            _size = other._size;
            std::memcpy(_ptr.get(), other._ptr.get(), _size);
            return *this;
        }

        constexpr memory(memory &&other) noexcept {
            _ptr = std::move(other._ptr);
            _size = other._size;
            other.release();
        }

        constexpr safe::memory & operator=(memory &&other) noexcept {
            if (&other == this) return *this;
    
            _ptr = std::move(other._ptr);
            _size = other._size;
            other.release();
    
            return *this;
        }
        
        /**
         * 
         * @return The size of the memory block in bytes.
         */
        constexpr size_t size() const { return _size; }

        /**
         * @note T must be a fundamental type or a POD (Plain Old Data) type
         * @return A value copy of type T at the given offset.
         */
        template<typename T> requires ((std::is_fundamental_v<T> || std::is_pod_v<T>) && sizeof(T) < sizeof(uintptr_t))
        constexpr return_of<T> get(const size_t offset) const {
            return *get_pointer<T>(offset);
        }
        
        /**
         * 
         * @tparam T The type of the value to get.
         * @param offset The offset in bytes from the start of the memory block. The data offset will be checked to ensure it is within bounds.
         * @note T must be a fundamental type or a POD (Plain Old Data) type.
         * @return A pointer to type T at the given offset.
         */
        template<typename T> requires ((std::is_fundamental_v<T> || std::is_pod_v<T>) && sizeof(T) >= sizeof(uintptr_t))
        constexpr return_of<ref<T>> get(const size_t offset) const {
            return *get_pointer<T>(offset);
        }

        /**
         * 
         * @tparam T The type of the value to set.
         * @param value The value to store at the given offset.
         * @param offset The offset in bytes from the start of the memory block. The data offset will be checked to ensure it is within bounds.
         */
        template<typename T> requires ((std::is_fundamental_v<T> || std::is_pod_v<T>) && sizeof(T) < sizeof(uintptr_t))
        constexpr void set(const T value, const size_t offset) {
            *get_pointer<T>(offset) = value;
        }

        /**
         * 
         * @tparam T The type of the value to set.
         * @param value The value to store at the given offset.
         * @param offset The offset in bytes from the start of the memory block. The data offset will be checked to ensure it is within bounds.
         */
        template<typename T> requires ((std::is_fundamental_v<T> || std::is_pod_v<T>) && sizeof(T) >= sizeof(uintptr_t))
        constexpr void set(const T & value, const size_t offset) {
            *get_pointer<T>(offset) = value;
        }

        /**
         * 
         * @tparam T The type of the value to set.
         * @param value The value to store at the given offset.
         * @param offset The offset in bytes from the start of the memory block. The data offset will be checked to ensure it is within bounds.
         */
        template<typename T> requires ((std::is_fundamental_v<T> || std::is_pod_v<T>) && sizeof(T) >= sizeof(uintptr_t))
        constexpr void set(const T * value, const size_t offset) {
            *get_pointer<T>(offset) = *value;
        }

        /**
         * Returns a span of type T starting at the given offset and with the given count. This is useful for accessing a range of memory as an array
         * in a type-safe and performant way.
         * @tparam T The type of the value to set.
         * @param value The value to store at the given offset.
         * @param offset The offset in bytes from the start of the memory block. The data offset will be checked to ensure it is within bounds.
         * @returns A span of type T starting at the given offset and with the given count.
         */
        template<typename T> requires ((std::is_fundamental_v<T> || std::is_pod_v<T>) && sizeof(T) < sizeof(uintptr_t))
        constexpr return_of<const std::span<T>> span(const size_t offset, const size_t count) const {
            //we need to ensure that the latest element (offset + count) is within bounds
            if (!is_safe_index<T>(offset + count)) {
                throw std::out_of_range("Offset is out of bounds");
            }
            return std::span<T>(reinterpret_cast<T *>(_ptr.get() + offset), count);
        }
    };
}

#endif //VOID_PTR_H
