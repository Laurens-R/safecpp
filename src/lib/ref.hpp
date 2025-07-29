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
        explicit constexpr ref(const T & data) : _data(data) {}        

        ref(const ref<T> & other) = delete;
        ref(ref<T> && other) noexcept = delete;
        ref<T> & operator=(const ref<T> & other) = delete;
        ref<T> & operator=(ref<T> && other) noexcept = delete;

        const T* operator->() const {
            return &_data;
        }
        
        [[nodiscard]] constexpr operator T() const {
            return _data;
        }

       [[nodiscard]] explicit constexpr operator const T &() const {
            return _data;
        }
    };
}

#endif //REF_HPP
