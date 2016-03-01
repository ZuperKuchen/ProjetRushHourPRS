add_executable(main main.c ../rushHour/game/game.c ../rushHour/piece/piece.c)
add_library(game STATIC main.c )
install(TARGETS game DESTINATION lib)
