cmake_minimum_required(VERSION 3.17)
project(Engine)

include(../cmake/CPM.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

CPMAddPackage(
        NAME EnTT 
        GITHUB_REPOSITORY skypjack/entt
        VERSION 3.5.2
        DOWNLOAD_ONLY True
)

CPMAddPackage(
        NAME imgui_sdl 
        GITHUB_REPOSITORY Tyyppi77/imgui_sdl
        GIT_TAG 0812f5ed05c0eb801fdb8ae71eb0cc75c95a8cff
        DOWNLOAD_ONLY True
)

CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.4
  )

CPMAddPackage(
	NAME imgui
	GITHUB_REPOSITORY ocornut/imgui
	VERSION 1.79
	DOWNLOAD_ONLY TRUE
)

if( NOT ${imgui_ADDED} )
	message( FATAL_ERROR "Could not find imgui" )
endif()

message( STATUS "Building imgui via: ${imgui_SOURCE_DIR}")

set(STAGING_ROOT ${CMAKE_CURRENT_BINARY_DIR}/imgui_staging)

file(GLOB headers 
	"${imgui_SOURCE_DIR}/imconfig.h"
	"${imgui_SOURCE_DIR}/imgui.h"
	"${imgui_SOURCE_DIR}/imgui_internal.h"
	"${imgui_SOURCE_DIR}/imstb_rectpack.h"
	"${imgui_SOURCE_DIR}/imstb_textedit.h"
	"${imgui_SOURCE_DIR}/imstb_truetype.h")

file(GLOB sources 
	"${imgui_SOURCE_DIR}/imgui.cpp"
	"${imgui_SOURCE_DIR}/imgui_demo.cpp"
	"${imgui_SOURCE_DIR}/imgui_draw.cpp"
	"${imgui_SOURCE_DIR}/imgui_widgets.cpp")

file(COPY ${headers} DESTINATION ${STAGING_ROOT}/include)

add_library(imgui STATIC ${sources} ${headers})

target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
                 $<INSTALL_INTERFACE:imgui-${PROJECT_VERSION}>)

packageProject(
  # the name of the target to export
  NAME imgui
  # the version of the target to export
  VERSION ${PROJECT_VERSION}
  # a temporary directory to create the config files
  BINARY_DIR ${PROJECT_BINARY_DIR}
  # location of the target's public headers
  INCLUDE_DIR ${STAGING_ROOT}/include
  # should match the target's INSTALL_INTERFACE include directory
  INCLUDE_DESTINATION include/imgui-${PROJECT_VERSION}
  # semicolon separated list of the project's dependencies
  DEPENDENCIES "")


set(ENGINE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include PARENT_SCOPE)

add_library(
        Engine SHARED
        #Includes
        include/engine.hh
        #Internal
        #Src
        src/engine.cc
        include/input.hh include/window.hh include/common.hh src/window.cc include/log.hh src/log.cc src/input.cc 
        include/utils.hh src/utils.cc include/objects/camera.hh include/vector.hh include/frame.hh 
        include/components/renderer.hh
        include/components/transform.hh
        include/texture_manager.hh src/texture_manager.cc
        include/texture.hh src/texture.cc
        internal/graphics_system.hh src/grapics_system.cc
        ${imgui_sdl_SOURCE_DIR}/imgui_sdl.cpp
        ${imgui_sdl_SOURCE_DIR}/imgui_sdl.h
)
        
if(EnTT_ADDED)
        add_library(EnTT INTERFACE)
        target_include_directories(EnTT INTERFACE ${EnTT_SOURCE_DIR}/src)
endif()

include_directories(Engine ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${headers})

target_link_libraries(Engine ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} EnTT imgui)

