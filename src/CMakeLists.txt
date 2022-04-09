cmake_minimum_required(VERSION 3.15)

find_package(SDL2 REQUIRED CONFIG)
find_package(box2d REQUIRED CONFIG)
# FIXME: sdl_image conan package still not adding properties
find_package(sdl_image REQUIRED CONFIG)
find_package(CLI11 REQUIRED CONFIG)
find_package(fmt REQUIRED CONFIG)
find_package(tinkerforge-bindings REQUIRED CONFIG)

add_executable(mygame main.cpp
                      Frog.cpp
                      Game.cpp
                      World.cpp)
target_include_directories(mygame PRIVATE include)

# FIXME: sdl_image conan package still not adding properties
target_link_libraries(mygame CLI11::CLI11 fmt::fmt box2d::box2d SDL2::SDL2main sdl_image::sdl_image tinkerforge::bindings)

install(TARGETS mygame
        PUBLIC_HEADER DESTINATION include
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

add_custom_command(TARGET mygame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/../assets/frog.png
        $<TARGET_FILE_DIR:mygame>

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/../assets/frog.png
        ${CMAKE_INSTALL_PREFIX}/bin/frog.png
        )
