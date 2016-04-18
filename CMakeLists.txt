cmake_minimum_required(VERSION 2.6)
project (RushHour)
include( CTest )
add_definitions(-std=c99 -g)

include_directories(src/game/ src/piece/ rushHour/ aneRouge/ solveur/ display/)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL REQUIRED sdl)
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})

install(FILES

        src/game/game.h
	src/piece/piece.h
	src/game/game_ar.h
	display/displayAR.h
	display/displayRH.h
	DESTINATION "include")
add_subdirectory(solveur)
add_subdirectory(src)
add_subdirectory(rushHour)
add_subdirectory(aneRouge)


set(CMAKE_INSTALL_PREFIX RushHour)
enable_testing()
