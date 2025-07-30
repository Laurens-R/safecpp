//
// Created by laure on 30/07/2025.
//

#ifndef PTR_HPP
#define PTR_HPP

#include <memory>

namespace safe {

    /*
     * ptr is almost not needed. But it exists to ensure that when dealing with pointers, we use the
     * same language and mental model in how we deal with them. And it allows for a natural way to share unique
     * pointers. at the same time it wraps the get method of the unique_ptr in an unsafe method, so when reading
     * the code it becomes a more explicit code smell that you are potentially doing something unsafe. the intent
     * behind this wrapper is also that you can pass a unique_ptr around without exposing methods that mess with
     * the pointer itself, like reset or release.
     */
    template<typename T>
    class ptr {
        std::unique_ptr<T> & _ptr;
    public:
        ptr(const std::unique_ptr<T> & p) : _ptr(p) {}

        /* We allow for copying this managed_ptr type, because the memory is managed through
         * the unique_ptr and so we can check it validity and it is safer to move around */
        ptr(const ptr<T> &other) : _ptr(other._ptr) { }
        ptr<T> & operator=(const ptr<T> &other) {
            if (other._ptr != _ptr) {
                _ptr = other._ptr;
            }

            return *this;
        };
        
        ptr(ptr<T> &&other) noexcept = delete;
        ptr<T> & operator=(ptr<T> &&other) noexcept = delete;
        
        T * operator->() const {
            return _ptr.get();
        }

        [[nodiscard]] bool is_valid() const {
            return _ptr != nullptr;
        }

        [[nodiscard]] T clone() const {
            return *_ptr.get();
        }
        
        [[nodiscard]] T * unsafe_get() const {
            return _ptr.get();
        }
    };

}

#endif //PTR_HPP
