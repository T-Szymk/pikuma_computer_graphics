
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

extern uint32_t window_width_px;
extern uint32_t window_height_px;
extern uint32_t background_colour_argb;
extern uint32_t grid_size_px;
extern SDL_Window*   window;
extern SDL_Renderer* renderer;
extern SDL_Texture*  colour_buffer_texture;
extern uint32_t* colour_buffer;

uint8_t initialise_window(void);
void    clear_colour_buffer(uint32_t*);
void    draw_rect_colour_buffer(uint32_t, uint32_t, uint32_t, uint32_t);
void    draw_grid_colour_buffer(uint32_t);
void    render_colour_buffer();
void    destroy_window(void);

#endif // _DISPLAY_H_