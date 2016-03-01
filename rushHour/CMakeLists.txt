add_executable(testPiece1 piece/piece.c piece/test_piece1.c) 
add_library(game STATIC game/game.c piece/piece.c )
install(TARGETS game DESTINATION lib)
