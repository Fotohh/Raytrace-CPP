cmake_minimum_required(VERSION 3.8)

project("raytrace-cpp")

add_executable(raytrace-cpp
        main.cc
)

find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(raytrace-cpp
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

