set(CMAKE_CXX_STANDARD 26)

add_library(safelib STATIC
        memory.hpp
        memory.cpp
        ref.hpp
        owner.hpp
        mut.hpp
        ranged.hpp
        assert.hpp
        var.hpp
)

target_sources(safelib
        PUBLIC
        FILE_SET CXX_MODULES BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} FILES safe.ixx
)

set_target_properties(safelib PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_MODULES safe.ixx
)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Add compile definitions based on build type
add_compile_definitions($<$<CONFIG:Debug>:SAFE_DEBUG>)
