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

# Box2D kütüphanesini indirme
FetchContent_Declare(
        Box2D
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.1
)

# Kütüphaneleri indir ve hazır hale getir
FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(Box2D)

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
        Physics.cpp
        Physics.h
)

# Kütüphaneleri bağlama
target_link_libraries(Main PRIVATE fmt)
target_link_libraries(Main PRIVATE sfml-graphics sfml-window sfml-system)
target_link_libraries(Main PRIVATE box2d)

# Box2D başlık dosyalarını dahil et
target_include_directories(Main PRIVATE ${box2d_SOURCE_DIR}/include ${box2d_BINARY_DIR})
