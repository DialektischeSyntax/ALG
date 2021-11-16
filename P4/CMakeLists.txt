cmake_minimum_required(VERSION 3.5)
project(p4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(p4
    cambio.cpp
    mochila.cpp
    main.cpp
)