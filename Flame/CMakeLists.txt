cmake_minimum_required(VERSION 2.8)

#Find GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

#find GLUT_Xmu
find_package(GLUT_Xmu)

#Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)


project(Flame)

configure_file(${CMAKE_SOURCE_DIR}/cmake/root_directory.hpp.in ${CMAKE_SOURCE_DIR}/include/root_directory.hpp)

set(
    SOURCES
    src/main.cpp
    src/particle.cpp
)

set(
    INCLUDES
    include/particle.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})


TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})


