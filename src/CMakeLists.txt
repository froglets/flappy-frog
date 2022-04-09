cmake_minimum_required(VERSION 3.15)


add_library(${PROJECT_NAME} INTERFACE)  # TODO: Change to proper library and add your files
set_target_properties(${PROJECT_NAME} PROPERTIES
        PUBLIC_HEADER ""  # TODO: Add your headers here
        )
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})

install(TARGETS ${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION include
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
