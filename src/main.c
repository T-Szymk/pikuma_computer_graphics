#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool is_running = false;

uint8_t initialise_window(void);
void    setup(void);
void    read_input(void);
void    update(void);
void    render(void);

int main(void) {

  if ( !initialise_window() ) {
    is_running = true;
  }

  // setup();

  while(is_running) {
    read_input();
    // update();
    render();
  }

  return 0;
}

uint8_t initialise_window(void) {

  if ( SDL_Init(SDL_INIT_EVERYTHING) ) {
    fprintf(stderr, "Error initialising SDL.\n");
    return 1;
  }
  
  // Create SDL Window
  window = SDL_CreateWindow( 
    NULL, // title
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    800,
    600,
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

  return 0;
}

void setup(void) {


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


}

void render(void) {

  SDL_SetRenderDrawColor( renderer, 64, 128, 255, 255);
  SDL_RenderClear( renderer );

  SDL_RenderPresent( renderer );

}
