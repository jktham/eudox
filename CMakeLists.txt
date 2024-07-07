cmake_minimum_required(VERSION 3.10.0)
project(eudox)

set(CMAKE_CXX_STANDARD 20)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES
	${PROJECT_SOURCE_DIR}/src/*.c
	${PROJECT_SOURCE_DIR}/src/*.cpp
	${PROJECT_SOURCE_DIR}/src/*.h
	${PROJECT_SOURCE_DIR}/src/*.hpp
	${PROJECT_SOURCE_DIR}/ext/src/*.c
	${PROJECT_SOURCE_DIR}/ext/src/*.cpp
	${PROJECT_SOURCE_DIR}/ext/src/*.cc
	${PROJECT_SOURCE_DIR}/ext/inc/*.h
	${PROJECT_SOURCE_DIR}/ext/inc/*.hpp
)

add_executable(eudox ${SOURCES})

target_include_directories(eudox PRIVATE src ext/inc)
if(WIN32)
	target_link_directories(eudox PRIVATE ext/lib)
	target_link_libraries(eudox PRIVATE libglfw3.a)
elseif(UNIX)
	target_link_libraries(eudox PRIVATE glfw)
endif()
target_link_libraries(eudox PRIVATE OpenGL::GL)

add_compile_definitions(GLFW_INCLUDE_NONE)
