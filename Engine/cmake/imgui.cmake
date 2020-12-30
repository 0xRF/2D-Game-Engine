include(CPM.cmake)


CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.4)

CPMAddPackage(
	NAME imgui
	GITHUB_REPOSITORY ocornut/imgui
	VERSION 1.79
	DOWNLOAD_ONLY TRUE)

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

###############################


    packageProject(
      # the name of the target to export
      NAME imgui_app_fw
      # the version of the target to export
      VERSION ${PROJECT_VERSION}
      # a temporary directory to create the config files
      BINARY_DIR ${PROJECT_BINARY_DIR}
      # location of the target's public headers
      INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include
      # should match the target's INSTALL_INTERFACE include directory
      INCLUDE_DESTINATION include/imgui_app_fw-${PROJECT_VERSION}
      # semicolon separated list of the project's dependencies
      DEPENDENCIES "imgui")

endif()

################

if(IMGUI_BUILD_EXAMPLES)

    file(GLOB example_sources 
        ${CMAKE_CURRENT_LIST_DIR}/examples/main.cpp)

    add_executable(imgui_example
        ${example_sources})
    
    target_include_directories(imgui_example 
        PRIVATE 
            ${imgui_SOURCE_DIR}/examples)
    
    target_link_libraries(imgui_example 
        PUBLIC
            imgui_app_fw)
endif()
