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


#ifndef PTR_HPP
#define PTR_HPP

#include <memory>

namespace safe {

    template<typename T>
    class ref_ptr {
        T * _ptr;

    protected:
        constexpr ref_ptr(T * p) : _ptr(p) {}
    public:
        static ref_ptr<T> create_from(T * p) {
            return ref_ptr<T>(p);
        }

        static ref_ptr<T> create_empty() {
            return ref_ptr<T>(nullptr);
        }

        constexpr ref_ptr() : _ptr(nullptr) {}

        /* We allow for copying this managed_ptr type, because the memory is managed through
         * the unique_ptr and so we can check it validity and it is safer to move around */
        constexpr ref_ptr(const ref_ptr<T> &other) : _ptr(other._ptr) { }

        constexpr ref_ptr<T> & operator=(const ref_ptr<T> &other) {
            if (&other != this) {
                _ptr = other._ptr;
            }

            return *this;
        };

        //the move instruction basically copy the references to the unique_ptr. But it's not a move in the sense
        //that it transfers ownership. That would be contradictory to the purpose of this class.
        constexpr ref_ptr(ref_ptr<T> &&other) noexcept : _ptr(other._ptr) {}

        ref_ptr<T> & operator=(ref_ptr<T> &&other) noexcept {
            if (&other != this) {
                _ptr = other._ptr;
            }
            return *this;
        }

        [[nodiscard]] constexpr T * operator->() const {
            return _ptr;
        }

        [[nodiscard]] constexpr bool is_valid() const {
            return _ptr == nullptr;
        }

        [[nodiscard]] constexpr T clone() const {
            return *_ptr;
        }

        [[nodiscard]] constexpr T * unsafe_pointer() const {
            return _ptr;
        }

        [[nodiscard]] constexpr T & unsafe_reference() const {
            return *_ptr;
        }


    };

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
        std::unique_ptr<T> * _ptr;;
    protected:
        constexpr ptr() : _ptr(nullptr){}
        constexpr ptr(std::unique_ptr<T> & p) : _ptr(&p) {}
    public:
        static ptr<T> create_from(std::unique_ptr<T> & p) {
            return ptr<T>(p);
        }

        static ptr<T> create_empty() {
            return ptr<T>();
        }

        /* We allow for copying this managed_ptr type, because the memory is managed through
         * the unique_ptr and so we can check it validity and it is safer to move around */
        constexpr ptr(const ptr<T> &other) : _ptr(other._ptr) { }

        constexpr ptr<T> & operator=(const ptr<T> &other) {
            if (&other != this) {
                _ptr = other._ptr;
            }

            return *this;
        };

        //the move instruction basically copy the references to the unique_ptr. But it's not a move in the sense
        //that it transfers ownership. That would be contradictory to the purpose of this class.
        constexpr ptr(ptr<T> &&other) noexcept : _ptr(other._ptr) {}

        ptr<T> & operator=(ptr<T> &&other) noexcept {
            if (&other != this) {
                _ptr = other._ptr;
            }
            return *this;
        }

        [[nodiscard]] constexpr T * operator->() const {
            return _ptr->get();
        }

        [[nodiscard]] constexpr bool is_valid() const {
            return _ptr != nullptr && _ptr->get() != nullptr;;
        }

        [[nodiscard]] constexpr T clone() const {
            return *_ptr->get();
        }

        [[nodiscard]] constexpr T * unsafe_pointer() const {
            return _ptr->get();
        }

        [[nodiscard]] constexpr T & unsafe_reference() const {
            return *_ptr->get();
        }

        //we consider this cast safe because we do check that the type is is convertible
        //and we know the poitner comes fro m a unique_ptr (so properly tracked)
        template<typename TCast>
        [[nodiscard]] constexpr ref_ptr<TCast> cast() const {
            static_assert(std::is_convertible_v<TCast *, T *>, "Cannot cast to a type that is not convertible.");
            static_assert(!std::is_same_v<T, TCast>, "Cannot cast to the same type.");
            return ref_ptr<TCast>::create_from(static_cast<TCast*>(_ptr->get()));
        }
    };


}

#endif //PTR_HPP
