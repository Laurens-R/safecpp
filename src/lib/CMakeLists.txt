set(CMAKE_CXX_STANDARD 26)

add_library(safelib
        memory.hpp
        memory.cpp
        readonly_ref.hpp
        owner.hpp
        mutable_ref.hpp
        ref_counter.hpp
)

target_sources(safelib
        PRIVATE
        FILE_SET CXX_MODULES BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} FILES safe.ixx
)

set_target_properties(safelib PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_MODULES safe.ixx
)