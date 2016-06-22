cmake_minimum_required(VERSION 3.5)
set(EXECUTABLE_NAME fastcraft)
project(fastcraft)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/Shader.h
        src/Player.cpp
        src/Player.h
        src/Camera.cpp
        src/Camera.h
        src/Block.cpp
        src/Block.h
        src/Chunk.cpp
        src/Chunk.h
        src/World.cpp
        src/World.h
        main.cpp
        )
add_executable(fastcraft ${SOURCE_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif ()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
    target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
    # or: target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_gl_LIBRARY})
    # target_link_libraries(${EXECUTABLE_NAME} m)  # if you use maths.h
endif ()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories($(GLEW_INCLUDE_DIRS))
    target_link_libraries(${EXECUTABLE_NAME} ${GLEW_LIBRARIES})
endif ()

find_package(GLFW 3 REQUIRED)
if (GLFW_FOUND)
    target_link_libraries(${EXECUTABLE_NAME} ${GLFW_LIBRARIES})
endif ()