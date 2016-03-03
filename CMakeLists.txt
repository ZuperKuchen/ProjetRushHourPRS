cmake_minimum_required(VERSION 2.6)
project (RushHour)

add_definitions(-std=c99 -g)

include_directories(src/game/ src/piece/ rushHour/)

install(FILES

        src/game/game.h
	src/piece/piece.h
	
	DESTINATION "include")

add_subdirectory(src)
add_subdirectory(rushHour)

set(CMAKE_INSTALL_PREFIX RushHour)
enable_testing()
