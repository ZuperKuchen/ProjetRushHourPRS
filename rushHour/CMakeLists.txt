add_executable(testPiece1 piece/piece.c piece/test_piece1.c) 
add_library(rushHour STATIC game/game.c piece/piece.c )
install(TARGETS rushHour DESTINATION lib)
