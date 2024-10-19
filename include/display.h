
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

/**
 * @brief initialise SDL window for rendering
 * 
 * @return uint8_t error code
 */
uint8_t initialise_window(void);

/**
 * @brief Doesn't actually clear the window but gradually tranitions background 
 * colours
 * 
 */
void    clear_colour_buffer(uint32_t*);

/**
 * @brief Draws rectangle which is filled with the inverse of the background 
 * colour
 * 
 * @param x_start Starting x coord of rectangle
 * @param y_start Starting y coord of rectangle
 * @param width   Width of rectangle
 * @param height  Height of rectangle
 */
void    draw_rect_colour_buffer(uint32_t x_start, uint32_t y_start, uint32_t width, uint32_t height);

/**
 * @brief Create a grid with a colour which is the inverse of the background
 * 
 * @param edge_size width/height between grid lines
 */
void    draw_grid_colour_buffer(uint32_t edge_size);

/**
 * @brief function to apply buffer to texture
 * 
 */
void    render_colour_buffer(void);

/**
 * @brief Close down window
 * 
 */
void    destroy_window(void);

#endif // _DISPLAY_H_