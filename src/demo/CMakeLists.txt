add_executable( safedemo 
    main.cpp
)

target_link_libraries( safedemo
    PUBLIC safelib
)