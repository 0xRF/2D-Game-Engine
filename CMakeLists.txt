cmake_minimum_required(VERSION 3.17)
project(Gaiyas)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(ext/imgui)
add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(GaiyasGame)
