cmake_minimum_required(VERSION 3.17)
project(Gaiyas)

set(CMAKE_CXX_STANDARD 20)

include(cmake/CPM.cmake)

CPMAddPackage(
        NAME          # The unique name of the dependency (should be the exported target's name)
        VERSION       # The minimum version of the dependency (optional, defaults to 0)
)

add_subdirectory(Engine)
add_subdirectory(GaiyasGame)
