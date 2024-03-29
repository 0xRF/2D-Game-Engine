project(imgui)

include(${CMAKE_SOURCE_DIR}/cmake/CPM.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

CPMAddPackage(
	NAME gimgui
	GITHUB_REPOSITORY ocornut/imgui
	VERSION 1.79
	DOWNLOAD_ONLY TRUE
  )

CPMAddPackage(
        NAME imgui_sdl 
        GITHUB_REPOSITORY Tyyppi77/imgui_sdl
        GIT_TAG 0812f5ed05c0eb801fdb8ae71eb0cc75c95a8cff
        DOWNLOAD_ONLY True
)

CPMAddPackage(
        NAME imgui-filebrowser
        GITHUB_REPOSITORY AirGuanZ/imgui-filebrowser
        GIT_TAG 02be68a5d5c6bc4ab1d18fabe0963dc737b226a6
        DOWNLOAD_ONLY True
)

if(${imgui_sdl_ADDED})
    if(${gimgui_ADDED})
        if(${imgui-filebrowser_ADDED})
           file(GLOB headers 
                    "${gimgui_SOURCE_DIR}/imconfig.h"
                    "${gimgui_SOURCE_DIR}/imgui.h"
                    "${gimgui_SOURCE_DIR}/imgui_internal.h"
                    "${gimgui_SOURCE_DIR}/imstb_rectpack.h"
                    "${gimgui_SOURCE_DIR}/imstb_textedit.h"
                    "${gimgui_SOURCE_DIR}/imstb_truetype.h"
                    "${gimgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.h"
                    "${imgui-filebrowser_SOURCE_DIR}/imfilebrowser.h"
           )

           file(GLOB sources 
                    "${gimgui_SOURCE_DIR}/imgui.cpp"
                    "${gimgui_SOURCE_DIR}/imgui_demo.cpp"
                    "${gimgui_SOURCE_DIR}/imgui_draw.cpp"
                    "${gimgui_SOURCE_DIR}/imgui_widgets.cpp"
                    "${gimgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp"
           )

            set(imgui_INCLUDE_DIR ${gimgui_SOURCE_DIR} PARENT_SCOPE)
            set(imgui_sdl_INCLUDE_DIR ${imgui_sdl_SOURCE_DIR} PARENT_SCOPE)
            set(imgui_INCLUDES ${headers} PARENT_SCOPE)
            set(imfilebrowser_INCLUDE_DIR ${imgui-filebrowser_SOURCE_DIR} PARENT_SCOPE)

            add_library(imgui SHARED ${headers} ${sources})
            include_directories(${SDL2_INCLUDE_DIR} ${gimgui_SOURCE_DIR} ${imgui-filebrowser_SOURCE_DIR})
            target_include_directories(imgui INTERFACE ${gimgui_SOURCE_DIR} ${SDL2_INCLUDE_DIR})
        endif()
    endif()
endif()
