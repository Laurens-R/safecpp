//
// Created by laure on 7/31/2025.
//

#ifndef INDEX_REF_HPP
#define INDEX_REF_HPP

#include <concepts>
#include <iterator>
#include <vector>
#include <array>

#include "ptr.hpp"

namespace safe {

    template<typename C, typename T>
    concept indexed_container_of = requires(C c) {
        { c.begin() } -> std::input_iterator;
        { c.end() } -> std::input_iterator;
        { c.size() } -> std::convertible_to<std::size_t>;
        { c.empty() } -> std::convertible_to<bool>;
        { c.at(std::declval<std::size_t>()) } -> std::convertible_to<T>;
        { c[std::declval<std::size_t>()] } -> std::convertible_to<T>;
        // Check that the container's value_type is T
        requires std::same_as<typename C::value_type, T>;
    };


   template<typename T>
    class index_ref {
    private:
        const void* _ptr;
        size_t _index;
        T(*_get_value)(const void*, size_t);
        bool(*_is_valid)(const void*, size_t);

        // Specialized implementations
        static T vector_get_value(const void* ptr, size_t idx) {
            return (*static_cast<const std::vector<T>*>(ptr))[idx];
        }

        static bool vector_is_valid(const void* ptr, size_t idx) {
            auto vec = static_cast<const std::vector<T>*>(ptr);
            return vec && idx < vec->size();
        }

        template<size_t N>
        static T array_get_value(const void* ptr, size_t idx) {
            return (*static_cast<const std::array<T, N>*>(ptr))[idx];
        }

        template<size_t N>
        static bool array_is_valid(const void* ptr, size_t idx) {
            return ptr && idx < N;
        }

        // Generic implementation
        template<typename Container>
        static T generic_get_value(const void* ptr, size_t idx) {
            return static_cast<const Container*>(ptr)->at(idx);
        }

        template<typename Container>
        static bool generic_is_valid(const void* ptr, size_t idx) {
            auto container = static_cast<const Container*>(ptr);
            return container && idx < container->size();
        }

    public:
        template<typename Container>
        index_ref(const Container& container, size_t index) noexcept
            : _ptr(&container)
            , _index(index) {
            if constexpr (std::is_same_v<Container, std::vector<T>>) {
                _get_value = &vector_get_value;
                _is_valid = &vector_is_valid;
            } else if constexpr (std::is_same_v<Container, std::array<T, Container::size()>>) {
                _get_value = &array_get_value<Container::size()>;
                _is_valid = &array_is_valid<Container::size()>;
            } else {
                _get_value = &generic_get_value<Container>;
                _is_valid = &generic_is_valid<Container>;
            }
        }

        //allow copies for now, but considering making it move-only for safety sake.
        /*constexpr index_ref(const index_ref& other) noexcept
            : _ptr(other._ptr)
            , _index(other._index)
            , _get_value(other._get_value)
            , _is_valid(other._is_valid) {}

        constexpr index_ref& operator=(const index_ref& other) noexcept {
            if (this != &other) {
                _ptr = other._ptr;
                _index = other._index;
                _get_value = other._get_value;
                _is_valid = other._is_valid;
            }
            return *this;
        }*/

        // Allow moves (for optimizing on return)
        index_ref(index_ref&& other) noexcept
            : _ptr(other._ptr)
            , _index(other._index)
            , _get_value(other._get_value)
            , _is_valid(other._is_valid) {}

        index_ref& operator=(index_ref&& other) noexcept {
            if (this != &other) {
                _ptr = other._ptr;
                _index = other._index;
                _get_value = other._get_value;
                _is_valid = other._is_valid;
            }
            return *this;
        }

        template<typename Container>
        index_ref(const ref_ptr<Container>& container, size_t index)
            : index_ref(*container.unsafe_pointer(), index) {}

        [[nodiscard]] T value() const {
            if (!is_valid()) {
                throw std::out_of_range("Invalid index reference");
            }
            return _get_value(_ptr, _index);
        }

        [[nodiscard]] bool is_valid() const {
            return _is_valid(_ptr, _index);
        }
    };
}

#endif //INDEX_REF_HPP
