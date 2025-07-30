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
            self._data += rhs._data;
            return self;
        }

        constexpr auto& operator-=(this const auto& self, const auto& rhs)  
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                 std::remove_cvref_t<decltype(rhs)>> {
            self._data -= rhs._data;
            return self;
        }

        constexpr auto& operator/=(this const auto& self, const auto& rhs)  
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                 std::remove_cvref_t<decltype(rhs)>> {
            self._data /= rhs._data;
            return self;
        }

        constexpr auto& operator*=(this const auto& self, const auto& rhs)  
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                 std::remove_cvref_t<decltype(rhs)>> {
            self._data *= rhs._data;
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
            return self._data + rhs._data;
        }

        constexpr T operator-(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data - rhs._data;
        }

        constexpr T operator*(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data * rhs._data;
        }

        constexpr T operator/(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data / rhs._data;
        }

        constexpr T operator%(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data % rhs._data;
        }

        //binary operators
        constexpr T operator&(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data & rhs._data;
        }

        constexpr T operator|(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data | rhs._data;
        }

        constexpr T operator^(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data ^ rhs._data;
        }

        //bit shift operators
        constexpr T operator<<(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data << rhs._data;
        }

        constexpr T operator>>(this const auto& self, const auto& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data >> rhs._data;
        }

        //comparison operators
        constexpr bool operator<=>(this const auto& self, const auto& rhs) 
          requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                              std::remove_cvref_t<decltype(rhs)>> {
            return self._data >= rhs._data;
        }


        //basic math operators
        constexpr T operator+(this const auto& self, const T& rhs)  
             requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                 std::remove_cvref_t<decltype(rhs)>> {
            return self._data + rhs;
        }

        constexpr T operator-(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data - rhs;
        }

        constexpr T operator*(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data * rhs;
        }

        constexpr T operator/(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data / rhs;
        }

        constexpr T operator%(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data % rhs;
        }

        //binary operators
        constexpr T operator&(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data & rhs;
        }

        constexpr T operator|(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data | rhs;
        }

        constexpr T operator^(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data ^ rhs;
        }

        //bit shift operators
        constexpr T operator<<(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data << rhs;
        }

        constexpr T operator>>(this const auto& self, const T& rhs) 
            requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                                std::remove_cvref_t<decltype(rhs)>> {
            return self._data >> rhs;
        }

        //comparison operators
        constexpr bool operator<=>(this const auto& self, const T& rhs) 
          requires std::same_as<std::remove_cvref_t<decltype(self)>, 
                              std::remove_cvref_t<decltype(rhs)>> {
            return self._data >= rhs;
        }
    };


}

#endif //COMMON_OPERATORS_HPP
