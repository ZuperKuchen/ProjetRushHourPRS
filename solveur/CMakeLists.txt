add_executable(solveur mainSolveur.c solveur.c ../display/displayAR.c ../display/displayRH.c ../display/displayGraph.c graph.c ../src/game/game_ar.c)
target_link_libraries(solveur game)

