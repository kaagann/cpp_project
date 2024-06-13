cmake_minimum_required(VERSION 3.27)
project(Project2)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

# fmt kütüphanesini indirme
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)

# SFML kütüphanesini indirme
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 2.6.1
)

# Kütüphaneleri indir ve hazır hale getir
FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(SFML)

# Proje kaynak dosyaları
add_executable(Main
        main.cpp
        Game.cpp
        Game.h
        Camera.cpp
        Camera.h
        Renderer.cpp
        Renderer.h
        Resources.cpp
        Resources.h
        Map.cpp
        Map.h
        Character.cpp
        Character.h
        Collisions.cpp
        Collisions.h
        Animation.cpp
        Animation.h
        Object.cpp
        Object.h
        CollectableItem.cpp
        CollectableItem.h
        Spike.cpp
        Spike.h
        RockHead.cpp
        RockHead.h
        OrangeItem.cpp
        OrangeItem.h
        EndPoint.cpp
        EndPoint.h
        EndPoint.h
)

# Kütüphaneleri bağlama
target_link_libraries(Main PRIVATE fmt)
target_link_libraries(Main PRIVATE sfml-graphics sfml-window sfml-system)
