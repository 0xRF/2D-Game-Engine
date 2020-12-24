cmake_minimum_required(VERSION 3.17)
project(Engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(ENGINE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include PARENT_SCOPE)

add_library(
        Engine SHARED
        #Includes
        include/engine.hh
        #Internal
        #Src
        src/engine.cc
        include/input.hh include/window.hh include/common.hh src/window.cc include/log.hh src/log.cc src/input.cc include/utils.hh src/utils.cc include/objects/camera.hh include/objects/object.hh include/vector.hh include/frame.hh)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(Engine ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

