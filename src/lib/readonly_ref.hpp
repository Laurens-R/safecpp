//
// Created by laure on 29/07/2025.
//

#ifndef REF_HPP
#define REF_HPP

namespace safe {
    template<typename T>
    class readonly_ref {
        const T & _data;
    public:
        explicit readonly_ref(const T & data) : _data(data) {}        
        readonly_ref(const readonly_ref<T> & other) = delete;
        readonly_ref(readonly_ref<T> && other) noexcept = delete;
        readonly_ref<T> & operator=(const readonly_ref<T> & other) = delete;
        readonly_ref<T> & operator=(readonly_ref<T> && other) noexcept = delete;
        
        explicit operator T() const {
            return _data;
        }

        explicit operator const T &() const {
            return _data;
        }
    };
}

#endif //REF_HPP
