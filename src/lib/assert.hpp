//
// Created by laure on 29/07/2025.
//

#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <cstdlib>
#include <iostream>
#include <cassert>

namespace safe {
    constexpr void safe_assert(const bool condition, const char * message) {
#ifdef SAFE_DEBUG
        assert(condition &&  message);
#else
        std::cerr << "FATAL - Assertion failed: " << message << std::endl;
        std::abort();
#endif
    }
}

#endif //ASSERT_HPP
