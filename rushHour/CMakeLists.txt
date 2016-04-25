add_executable(rushHourCommand rushHourCommand.c rushHour.c)

#TARGET_LINK_LIBRARIES(rushHour game ${SDL_LIBRARIES} )

target_link_libraries(rushHourCommand game )


add_executable(rushHourGraphic ../solveur/graph.c ../display/displayAR.c ../display/displayRH.c ../display/displayGraph.c ../solveur/solveur.c rushHour.c rushHourGraphic.c config_sdl.c ../src/game/game_ar.c )
target_link_libraries(rushHourGraphic game ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} SDL2  SDL2_image SDL2_ttf)
