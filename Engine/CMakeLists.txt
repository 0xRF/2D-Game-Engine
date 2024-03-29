cmake_minimum_required(VERSION 3.17)
project(Engine)

include(${CMAKE_SOURCE_DIR}/cmake/CPM.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)


CPMAddPackage(
        NAME EnTT 
        GITHUB_REPOSITORY skypjack/entt
        VERSION 3.5.2
        DOWNLOAD_ONLY True
)

if(EnTT_ADDED)
        add_library(EnTT INTERFACE)
        target_include_directories(EnTT INTERFACE ${EnTT_SOURCE_DIR}/src)
endif()

CPMAddPackage(
  NAME pjsoncons
  VERSION 0.162.0
  GITHUB_REPOSITORY danielaparker/jsoncons
)

if (pjsoncons_ADDED)
  add_library(pjsoncons INTERFACE IMPORTED)
  target_include_directories(pjsoncons INTERFACE ${pjsoncons_SOURCE_DIR}/include)
endif()

set(ENGINE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include PARENT_SCOPE)

add_library(
        Engine SHARED
        #Includes
        include/engine.hh
        #Internal
        #Src
        src/engine.cc
        include/input.hh include/window.hh include/common.hh src/window.cc include/log.hh src/log.cc src/input.cc 
        include/utils.hh src/utils.cc include/objects/camera.hh include/vector.hh
        include/math.hh
        include/components/renderer.hh
        #        include/components/transform.hh
        include/components/position.hh
        include/components/box_collider.hh
        include/components/polygon_collider.hh
        include/components/rotatable.hh
        include/texture_manager.hh src/texture_manager.cc
        include/texture.hh src/texture.cc
        include/systems/movement_system.hh src/movement_system.cc
        include/components/component.hh
        include/components/scale.hh
        include/resource.hh
        include/resource_manager.hh
        src/resource_manager.cc

        include/systems/physics_system.hh include/systems/collision_system.hh
        src/physics_system.cc src/collision_system.cc
        include/graphics.hh src/graphics.cc
 
        "${imgui_sdl_INCLUDE_DIR}/imgui_sdl.cpp"
        "${imgui_sdl_INCLUDE_DIR}/imgui_sdl.h"
)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${imgui_INCLUDE_DIR} ${imgui_sdl_INCLUDE_DIR} ${imfilebrowser_INCLUDE_DIR})

target_link_libraries(Engine ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} EnTT imgui pjsoncons)

