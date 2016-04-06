add_executable(rushHour rushHour.c)
add_executable(solveur solveur.c)
target_link_libraries(solveur game)
target_link_libraries(rushHour game)
