cmake_minimum_required (VERSION 2.6)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL -pthread")

add_executable (catris
	main.cpp
	image.cpp
	field.cpp
	brick.cpp
	field.cpp
	helpers.cpp)
target_link_libraries (catris SDL SDL_image pthread)
