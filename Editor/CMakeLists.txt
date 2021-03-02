project(Editor)

add_executable(Editor 
    src/main.cc 
    src/resource_window.cc
    include/resource_window.hh
    src/inspector_window.cc
    include/inspector_window.hh

)
target_include_directories(Editor PUBLIC ${ENGINE_INCLUDE_DIR} ${imfilebrowser_INCLUDE_DIR})
target_link_libraries(Editor Engine)
