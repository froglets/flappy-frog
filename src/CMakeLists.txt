cmake_minimum_required(VERSION 3.15)

find_package(SDL2 REQUIRED CONFIG)
find_package(box2d REQUIRED CONFIG)
# FIXME: sdl_image conan package still not adding properties
find_package(sdl_image REQUIRED CONFIG)
find_package(SDL2_mixer REQUIRED CONFIG)
find_package(fmt REQUIRED CONFIG)
find_package(tinkerforge-bindings REQUIRED CONFIG)

if(NOT IOS)
        find_package(CLI11 REQUIRED CONFIG)
else()
        set(MACOSX_BUNDLE_SHORT_VERSION_STRING 1.0)
        set(MACOSX_BUNDLE_BUNDLE_VERSION 1.0)
        set(MACOSX_BUNDLE_GUI_IDENTIFIER froglets.flappyfrog)
        set(ADDITIONAL_PROJECT_FILES ../ios/LaunchScreen.storyboard)
endif()

add_executable(mygame main.cpp
                      Frog.cpp
                      Pipe.cpp
                      Game.cpp
                      World.cpp
                      Frog.hpp
                      Pipe.hpp
                      Game.hpp
                      World.hpp
                      Platform.hpp
                      ${ADDITIONAL_PROJECT_FILES})


target_include_directories(mygame PRIVATE include)

# FIXME: sdl_image conan package still not adding properties
target_link_libraries(mygame fmt::fmt box2d::box2d SDL2::SDL2main sdl_image::sdl_image SDL2_mixer::SDL2_mixer tinkerforge::bindings)

if(APPLE)
        target_link_libraries(mygame -framework CoreServices -framework ImageIO)
endif()

if(NOT IOS)
        target_link_libraries(mygame CLI11::CLI11)
endif()

install(TARGETS mygame
        PUBLIC_HEADER DESTINATION include
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        BUNDLE DESTINATION bin)

file(GLOB ASSETS "${CMAKE_CURRENT_SOURCE_DIR}/../assets/*.*")
     
foreach(asset ${ASSETS})
        add_custom_command(TARGET mygame POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${asset}
                $<TARGET_FILE_DIR:mygame>

                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${asset}
                ${CMAKE_INSTALL_PREFIX}/bin)
endforeach(asset)
