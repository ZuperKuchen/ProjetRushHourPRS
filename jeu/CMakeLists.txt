add_executable(main main.c)
add_library(game STATIC main.c )
install(TARGETS game DESTINATION lib)
