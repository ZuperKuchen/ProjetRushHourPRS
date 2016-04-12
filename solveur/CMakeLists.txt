add_executable(solveur solveur.c displayAR.c displayRH.c graph.c ../src/game/game_ar.c)
target_link_libraries(solveur game)

