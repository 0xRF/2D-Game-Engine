project(Editor)

add_executable(Editor src/main.cc)
target_include_directories(Editor PUBLIC ${ENGINE_INCLUDE_DIR})
target_link_libraries(Editor Engine)
