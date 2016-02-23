cmake_minimum_required(VERSION 2.6)
project (RushHour)

add_definitions(-std=c99)

include_directories(rushHour/game/ rushHour/piece/)

install(FILES

        rushHour/game/game.h
	rushHour/piece/piece.h
	
	DESTINATION "include")

add_subdirectory(rushHour)

set(CMAKE_INSTALL_PREFIX RushHour)
enable_testing()
