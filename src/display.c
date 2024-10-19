
#include "display.h"

uint8_t initialise_window(void) {

  if ( SDL_Init(SDL_INIT_EVERYTHING) ) {
    fprintf(stderr, "Error initialising SDL.\n");
    return 1;
  }

  // Use SDL to determine max available resolution
  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);

  window_width_px  = display_mode.w;
  window_height_px = display_mode.h;
  
  // Create SDL Window
  window = SDL_CreateWindow( 
    NULL, // title
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    window_width_px,
    window_height_px,
    SDL_WINDOW_BORDERLESS
  );

  if ( !window ) {
    fprintf(stderr, "Error creating SDL window\n");
    return 1;
  }

  // Create SDL renderer
  renderer = SDL_CreateRenderer(
    window,
    -1,
     0 /* default flags */
  );

  if ( !renderer ) {
    fprintf(stderr, "Error creating SDL renderer\n");
    return 1;
  }
  
  // Set SDL to use real full screen
  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  return 0;
}

void clear_colour_buffer(uint32_t *colour) {

  uint32_t colour_rgb = (*colour & 0x00FFFFFFu);

  for ( uint32_t y = 0; y < window_height_px; y++ ) {
    for ( uint32_t x = 0; x < window_width_px; x++ ) {
      colour_buffer[( y * window_width_px ) + x] = *colour; // ARGB
    }
  }
  
  // reset colour to 0 when rgb is at its max value
  if ( ((colour_rgb >> 16) & 0xFFu) == 0xFFu ) {
    colour_rgb = 0;
  // if g is max value, increment r value
  } else if ( ((colour_rgb >> 8) & 0xFFu) == 0xFFu ) {
    uint8_t colour_r = (uint8_t)(colour_rgb >> 16);
    colour_r++;
    colour_rgb &= 0xFF00FFFFu;
    colour_rgb |= ((uint32_t)(colour_r) << 16); // populate red in rgb
  // if b is max value, increment g value
  } else if ( (colour_rgb & 0xFFu) == 0xFFu ) {
    uint8_t colour_g = (uint8_t)(colour_rgb >> 8);
    colour_g++;
    colour_rgb &= 0xFFFF00FFu;
    colour_rgb |= ((uint32_t)(colour_g) << 8); // populate green in rgb
  // else increment b value
  } else {
    colour_rgb++;
  }

  *colour &= 0xFF000000u;
  *colour |= colour_rgb;
}

void draw_rect_colour_buffer(uint32_t x_start, uint32_t y_start, uint32_t width, uint32_t height) {

  for ( uint32_t y = y_start; y < (y_start + height); y++ ) {
    for ( uint32_t x = x_start; x < (x_start + width); x++ ) {
      colour_buffer[( y * window_width_px ) + x] ^= 0x00FFFFFF; // invert the colour bits
    }
  }

}

void draw_grid_colour_buffer(uint32_t edge_size) {

  for ( uint32_t y = 0; y < window_height_px; y++ ) {
    for ( uint32_t x = 0; x < window_width_px; x++ ) {
      if ( !(y % edge_size) || !(x % edge_size) ) {
        colour_buffer[( y * window_width_px ) + x] ^= 0x00FFFFFF; // invert the colour bits
      }
    }
  }
  
}

void render_colour_buffer(void) {

  // copy buffer into the texture
  SDL_UpdateTexture(
    colour_buffer_texture,
    NULL, // used if we want to select a subsection of the texture
    colour_buffer,
    (int)(window_width_px * sizeof(uint32_t))
  );
    // copy texture to renderer 
  SDL_RenderCopy(renderer, colour_buffer_texture, NULL, NULL);
}

void destroy_window(void) {

  free(colour_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit(); // opposite of SDL_Init()

}