//
// Created by laure on 28/07/2025.
//

#ifndef VOID_PTR_H
#define VOID_PTR_H

#include <stdexcept>
#include <type_traits>

namespace safe {
    class memory {
    public:
        template<typename T>
        constexpr bool is_safe_index(const size_t offset) const {
            return (offset + sizeof(T)) < _size;
        }
        
    private:
        mutable std::byte *_ptr = nullptr;
        mutable size_t _size = 0;

        template<typename T>
        constexpr T * get_pointer(const size_t offset) const {
            const uintptr_t mask = ((offset + sizeof(T)) < _size);
            auto base = reinterpret_cast<uintptr_t>(_ptr + offset);
            return reinterpret_cast<T *>(base * mask);
        }

        void release() const;
        
    public:
        memory(size_t size);
        ~memory();

        memory(const memory &other);
        memory &operator=(const memory &other);

        memory(memory &&other) noexcept;
        memory &operator=(memory &&other) noexcept;

        constexpr size_t size() const { return _size; }

        template<typename T> requires ((std::is_fundamental_v<T> || std::is_pod_v<T>) && sizeof(T) < sizeof(uintptr_t))
        constexpr T get(const size_t offset) const {
            return *get_pointer<T>(offset);
        }
        
        template<typename T> requires ((std::is_fundamental_v<T> || std::is_pod_v<T>) && sizeof(T) >= sizeof(uintptr_t))
        constexpr const T * get(const size_t offset) const {
            return *get_pointer<T>(offset);
        }

        template<typename T> requires ((std::is_fundamental_v<T> || std::is_pod_v<T>) && sizeof(T) < sizeof(uintptr_t))
        constexpr void set(const T value, const size_t offset) {
            *get_pointer<T>(offset) = value;
        }
        
        template<typename T> requires ((std::is_fundamental_v<T> || std::is_pod_v<T>) && sizeof(T) >= sizeof(uintptr_t))
        constexpr void set(const T & value, const size_t offset) {
            *get_pointer<T>(offset) = value;
        }

        template<typename T> requires ((std::is_fundamental_v<T> || std::is_pod_v<T>) && sizeof(T) >= sizeof(uintptr_t))
        constexpr void set(const T * value, const size_t offset) {
            *get_pointer<T>(offset) = *value;
        }
    };

    memory make_memory(size_t size);
}

#endif //VOID_PTR_H
