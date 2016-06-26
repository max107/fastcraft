cmake_minimum_required(VERSION 3.5)
set(EXECUTABLE_NAME fastcraft)
project(fastcraft)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/Object.cpp
        src/Object.h
        src/Fastcraft.cpp
        src/Fastcraft.h
        src/Settings.h
        #        src/Shader.h
        src/Player.cpp
        src/Player.h
        src/Camera.cpp
        src/Camera.h
        src/Block.cpp
        src/Block.h
        #        src/Chunk.cpp
        #        src/Chunk.h
        #        src/World.cpp
        #        src/World.h
        main.cpp
        )

add_executable(fastcraft ${SOURCE_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_TTF REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

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