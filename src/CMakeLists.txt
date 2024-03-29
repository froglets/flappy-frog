cmake_minimum_required(VERSION 3.15)

find_package(SDL2 REQUIRED CONFIG)
find_package(box2d REQUIRED CONFIG)
# FIXME: sdl_image conan package still not adding properties
find_package(sdl_image REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)
find_package(SDL2_mixer REQUIRED CONFIG)
find_package(fmt REQUIRED CONFIG)
find_package(tinkerforge-bindings REQUIRED CONFIG)

if (NOT IOS)
        find_package(CLI11 REQUIRED CONFIG)
else()
        set(MACOSX_BUNDLE_SHORT_VERSION_STRING 1.0)
        set(MACOSX_BUNDLE_BUNDLE_VERSION 1.0)
        set(MACOSX_BUNDLE_GUI_IDENTIFIER froglets.flappyfrog)
        set(ADDITIONAL_PROJECT_FILES ../ios/LaunchScreen.storyboard)
endif()  

add_executable(flappy-frog main.cpp
                           Frog.cpp
                           Pipe.cpp
                           Game.cpp
                           World.cpp
                           Frog.hpp
                           Pipe.hpp
                           Game.hpp
                           World.hpp
                           Platform.hpp
                           Layer.cpp 
                           Layer.hpp
                           ObstacleManager.cpp 
                           ObstacleManager.hpp
                           ScreenManager.cpp 
                           ScreenManager.hpp
                           StartScreen.cpp 
                           StartScreen.hpp
                           GameScreen.cpp 
                           GameScreen.hpp
                           EndScreen.cpp 
                           EndScreen.hpp
                           Text.cpp
                           Text.hpp
                           ${ADDITIONAL_PROJECT_FILES})

target_include_directories(flappy-frog PRIVATE include)

# FIXME: sdl_image conan package still not adding properties
target_link_libraries(flappy-frog fmt::fmt box2d::box2d SDL2::SDL2main 
                      sdl_image::sdl_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer tinkerforge::bindings)

if (NOT IOS)
        target_link_libraries(flappy-frog CLI11::CLI11)
endif()
              
if(APPLE)
        find_library(CORE_SERVICES_LIBRARY CoreServices )
        find_library(IMAGEIO_LIBRARY ImageIO )
        target_link_libraries(flappy-frog ${CORE_SERVICES_LIBRARY} ${IMAGEIO_LIBRARY})
endif()

install(TARGETS flappy-frog
        PUBLIC_HEADER DESTINATION include
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        BUNDLE DESTINATION bin)

file(GLOB ASSETS "${CMAKE_CURRENT_SOURCE_DIR}/../assets/*.*")
     
foreach(asset ${ASSETS})
        add_custom_command(TARGET flappy-frog POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${asset}
                $<TARGET_FILE_DIR:flappy-frog>

                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${asset}
                ${CMAKE_INSTALL_PREFIX}/bin)
endforeach(asset)
