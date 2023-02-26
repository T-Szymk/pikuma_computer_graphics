#include "display.h"

/* Globals, Statics and Constants */

uint32_t window_width_px = 800;
uint32_t window_height_px = 600;

uint32_t background_colour_argb = 0xFF000000;
uint32_t grid_size_px = 20;

SDL_Window*   window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture*  colour_buffer_texture = NULL;

uint32_t* colour_buffer = NULL;

bool is_running = false;

/* Forward Declarations */

uint8_t setup(void);
void    read_input(void);
void    update(void);
void    render(void);

/*** Main ***/

int main(void) {

  if ( !initialise_window() ) {
    is_running = true;
  }

  setup();

  while(is_running) {
    read_input();
    // update();
    render();
  }  

  destroy_window();

  return 0;
}

/* Function Definitions */


uint8_t setup(void) {

  // Allocate the required memory in bytes to hold the color buffer
  colour_buffer = (uint32_t*)malloc(sizeof(uint32_t)*window_width_px*window_height_px);

  // Create texture to be passed to renderer
  colour_buffer_texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ARGB8888, //ARGB888 32b
    SDL_TEXTUREACCESS_STREAMING, // used as we will be accessing the texture a lot
    window_width_px,
    window_height_px
  );

  if ( !colour_buffer_texture ) {
    fprintf(stderr, "Error creating SDL texture\n");
    return 1;
  }

  return 0;
}

void read_input(void) {

  SDL_Event event;
  SDL_PollEvent( &event );

  switch ( event.type ) {

    case SDL_QUIT: // window has been closed

      is_running = false;
      
    break;

    case SDL_KEYDOWN:

      if ( event.key.keysym.sym == SDLK_ESCAPE ) { // escape key is pressed
        is_running = false;
      }

    break;

  }
}

void update(void) {
// Todo:

}

void render(void) {

  //SDL_SetRenderDrawColor( renderer, 0, 128, 64, 255);
  //SDL_RenderClear( renderer );

  clear_colour_buffer( &background_colour_argb ); // ARGB
  draw_grid_colour_buffer(grid_size_px);
  draw_rect_colour_buffer(100, 100, 100, 100);
  render_colour_buffer();

  SDL_RenderPresent( renderer );

}
