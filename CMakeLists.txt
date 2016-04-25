
cmake_minimum_required(VERSION 2.6)
project (RushHour)
include( CTest )
add_definitions(-std=c99 -g)

include_directories(src/game/ src/piece/ rushHour/ aneRouge/ solveur/ display/)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2_REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_image_REQUIRED sdl2_image)
PKG_SEARCH_MODULE(SDL2_ttf_REQUIRED SDL2_ttf)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS}
${SDL2_IMAGE_INCLUDE_DIR}
${SDL2_TTF_INCLUDE_DIR})


install(FILES

        src/game/game.h
	src/piece/piece.h
	src/game/game_ar.h
	display/displayAR.h
	display/displayRH.h
	rushHour/config_sdl.h
	rushHour/rushHour.h
	solveur/solveur.h
	DESTINATION "include")
add_subdirectory(solveur)
add_subdirectory(src)
add_subdirectory(rushHour)
add_subdirectory(aneRouge)


set(CMAKE_INSTALL_PREFIX RushHour)
enable_testing()
