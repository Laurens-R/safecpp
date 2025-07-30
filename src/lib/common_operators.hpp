//
// Created by laure on 30/07/2025.
//

#ifndef COMMON_OPERATORS_HPP
#define COMMON_OPERATORS_HPP

namespace safe {

    template<typename T>
    class common_operators {
    protected:

        //basic math operators
        constexpr auto& operator+=(this const auto& self, const auto& rhs)  
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                 std::remove_cvref_t<decltype(rhs)>> {
            self._value += rhs.unsafe_get();
            return self;
        }

        constexpr auto& operator-=(this const auto& self, const auto& rhs)  
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                 std::remove_cvref_t<decltype(rhs)>> {
            self._value -= rhs.unsafe_get();
            return self;
        }

        constexpr auto& operator/=(this const auto& self, const auto& rhs)  
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                 std::remove_cvref_t<decltype(rhs)>> {
            self._value /= rhs.unsafe_get();
            return self;
        }

        constexpr auto& operator*=(this const auto& self, const auto& rhs)  
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                 std::remove_cvref_t<decltype(rhs)>> {
            self._value *= rhs.unsafe_get();
            return self;
        }
    };

    
    template<typename T>
    class common_operators_unmutable {
    protected:

        //basic math operators
        constexpr T operator+(this const auto& self, const auto& rhs)  
             requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                 std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() + rhs.unsafe_get();
        }

        constexpr T operator-(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() - rhs.unsafe_get();
        }

        constexpr T operator*(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() * rhs.unsafe_get();
        }

        constexpr T operator/(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() / rhs.unsafe_get();
        }

        constexpr T operator%(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() % rhs.unsafe_get();
        }

        //binary operators
        constexpr T operator&(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() & rhs.unsafe_get();
        }

        constexpr T operator|(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() | rhs.unsafe_get();
        }

        constexpr T operator^(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() ^ rhs.unsafe_get();
        }

        //bit shift operators
        constexpr T operator<<(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() << rhs.unsafe_get();
        }

        constexpr T operator>>(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() >> rhs.unsafe_get();
        }

        //comparison operators
        constexpr bool operator<=>(this const auto& self, const auto& rhs) 
          requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                              std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() >= rhs.unsafe_get();
        }


        //basic math operators
        constexpr T operator+(this const auto& self, const T& rhs)  
             requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                 std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() + rhs;
        }

        constexpr T operator-(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() - rhs;
        }

        constexpr T operator*(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() * rhs;
        }

        constexpr T operator/(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() / rhs;
        }

        constexpr T operator%(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() % rhs;
        }

        //binary operators
        constexpr T operator&(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() & rhs;
        }

        constexpr T operator|(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() | rhs;
        }

        constexpr T operator^(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() ^ rhs;
        }

        //bit shift operators
        constexpr T operator<<(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() << rhs;
        }

        constexpr T operator>>(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() >> rhs;
        }

        //comparison operators
        constexpr bool operator<=>(this const auto& self, const T& rhs) 
          requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                              std::remove_cvref_t<decltype(rhs)>> {
            return self.unsafe_get() >= rhs;
        }
    };


}

#endif //COMMON_OPERATORS_HPP
