add_library(rushHour STATIC game/game.c piece/piece.c piece/test_piece.c game/test_game.c)
install(TARGETS rushHour DESTINATION lib)
