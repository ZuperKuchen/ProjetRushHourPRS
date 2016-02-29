cmake_minimum_required(VERSION 2.6)
project (RushHour)

add_definitions(-std=c99)

include_directories(rushHour/game/ rushHour/piece/ jeu/)

install(FILES

        rushHour/game/game.h
	rushHour/piece/piece.h
	
	DESTINATION "include")

add_subdirectory(rushHour)
add_subdirectory(jeu)

set(CMAKE_INSTALL_PREFIX RushHour)
enable_testing()
