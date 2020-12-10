project(GaiyasGame)

add_executable(GaiyasGame src/main.cc)
target_include_directories(GaiyasGame PUBLIC ${ENGINE_INCLUDE_DIR})
target_link_libraries(GaiyasGame Engine)
