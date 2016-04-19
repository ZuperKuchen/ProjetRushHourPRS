add_executable(rushHour rushHour.c config_sdl.c)
#TARGET_LINK_LIBRARIES(rushHour game ${SDL_LIBRARIES} )

target_link_libraries(rushHour game ${SDL2_LIBRARIES}
${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} SDL2  SDL2_ttf)

