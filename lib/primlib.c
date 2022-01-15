#include "dimensions.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "primlib.h"
static SDL_Renderer *renderer = NULL;
static SDL_Window *window = NULL;

struct RGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

static struct RGB colors[COLOR_MAX] = {
    {0, 0, 0},     {255, 0, 0},   {0, 255, 0},   {0, 0, 255},
    {0, 255, 255}, {255, 0, 255}, {255, 255, 0}, {255, 255, 255}};

// Screen dimension constants
const int SCREEN_WIDTH = MAX_W;//800;
const int SCREEN_HEIGHT = MAX_H;//600;

void gfx_pixel(int x, int y, enum color c) {
  pixelRGBA(renderer, x, y, colors[c].r, colors[c].g, colors[c].b, 255);
}

void gfx_line(int x1, int y1, int x2, int y2, enum color c) {
  assert(c < COLOR_MAX);
  lineRGBA(renderer, x1, y1, x2, y2, colors[c].r, colors[c].g, colors[c].b,
           255);
}

void gfx_wline(int x1, int y1, int x2, int y2, enum color c, int width) {
  assert(c < COLOR_MAX);
  thickLineRGBA(renderer, x1, y1, x2, y2, width, colors[c].r, colors[c].g, colors[c].b,
           255);
}

void gfx_filledTriangle(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3, enum color c) {
  assert(c < COLOR_MAX);
  Sint16 xtab[] = {x1, x2, x3};
  Sint16 ytab[] = {y1, y2, y3};
  filledPolygonRGBA(renderer, xtab, ytab, 3, colors[c].r, colors[c].g, colors[c].b,
                255);
}

void gfx_rect(int x1, int y1, int x2, int y2, enum color c) {
  assert(c < COLOR_MAX);
  rectangleRGBA(renderer, x1, y1, x2, y2, colors[c].r, colors[c].g, colors[c].b,
                255);
}

void gfx_filledRect(int x1, int y1, int x2, int y2, enum color c) {
  assert(c < COLOR_MAX);
  boxRGBA(renderer, x1, y1, x2, y2, colors[c].r, colors[c].g, colors[c].b, 255);
}

void gfx_circle(int x, int y, int r, enum color c) {
  assert(c < COLOR_MAX);
  circleRGBA(renderer, x, y, r, colors[c].r, colors[c].g, colors[c].b, 255);
}

void gfx_filledCircle(int x, int y, int r, enum color c) {
  assert(c < COLOR_MAX);
  filledCircleRGBA(renderer, x, y, r, colors[c].r, colors[c].g, colors[c].b,
                   255);
}

int gfx_screenWidth() { return SCREEN_WIDTH; }

int gfx_screenHeight() { return SCREEN_HEIGHT; }

void gfx_updateScreen() {
  SDL_RenderPresent(renderer);
  SDL_RenderClear(renderer);
}

void gfx_textout(int x, int y, const char *s, enum color c) {
  assert(c < COLOR_MAX);
  stringRGBA(renderer, x, y, s, colors[c].r, colors[c].g, colors[c].b, 255);
}

SDL_Event gfx_getEvent() {
  SDL_Event event;
  while (1) {
    SDL_WaitEvent(&event);

    if (event.type == SDL_KEYDOWN ||
        event.type == SDL_USEREVENT ||
        event.type == SDL_QUIT)
      break;
  };
  return event;
}

static void gfx_close() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int gfx_init() {

  /* Initialize SDL */
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    return 1;
  }
  atexit(gfx_close);    //https://stackoverflow.com/questions/19402417/when-should-atexit-be-used

  window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "Window could not be created! SDL Error: %s\n", SDL_GetError());
    return 2;
  } else {
    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    }

    if (renderer == NULL) {
      fprintf(stderr,"Renderer could not be created! SDL Error: %s\n", SDL_GetError());
      return 3;
    }
  }

  SDL_Delay(10);
  return 0;
}
