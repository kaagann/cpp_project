cmake_minimum_required(VERSION 3.27)
project(Project2)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)   # here

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)


FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(SFML)


add_executable(Main main.cpp
        Game.cpp
        Game.h
        Game.h
        Camera.cpp
        Camera.h
        Renderer.cpp
        Renderer.h
        Renderer.h)

target_link_libraries(Main fmt)
target_link_libraries(Main sfml-graphics)
