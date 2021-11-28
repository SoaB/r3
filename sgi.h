#ifndef HEADER_A60AE57AA09DF288
#define HEADER_A60AE57AA09DF288

#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Global variable definition

typedef struct tag_RGBA {
  union {
    struct {
      unsigned char r;
      unsigned char g;
      unsigned char b;
      unsigned char a;
    };
    uint32_t color;
  };
} RGBA;
//
const RGBA RGB_Black = {.color = 0xFF000000};
const RGBA RGB_Red = {.color = 0xFF0000FF};
const RGBA RGB_Green = {.color = 0xFF00FF00};
const RGBA RGB_Blue = {.color = 0xFFFF0000};
const RGBA RGB_Cyan = {.color = 0xFFFFFF00};
const RGBA RGB_Magenta = {.color = 0xFFFF00FF};
const RGBA RGB_Yellow = {.color = 0xFF00FFFF};
const RGBA RGB_White = {.color = 0xFFFFFFFF};
const RGBA RGB_Gray = {.color = 0xFF808080};
const RGBA RGB_Grey = {.color = 0xFFC0C0C0};
const RGBA RGB_Maroon = {.color = 0xFF000080};
const RGBA RGB_Darkgreen = {.color = 0xFF008000};
const RGBA RGB_Navy = {.color = 0xFF800000};
const RGBA RGB_Teal = {.color = 0xFF808000};
const RGBA RGB_Purple = {.color = 0xFF800080};
const RGBA RGB_Olive = {.color = 0xFF008080};
//
typedef struct tag_Sgi {
  SDL_Window *Window;
  SDL_Renderer *Renderer;
  SDL_Event event;
  RGBA SelColor;
  uint32_t w;
  uint32_t h;
  const uint8_t *inkeys;
  int mouseX;
  int mouseY;
  bool LMB;
  bool RMB;
} Sgi_t;
// instance of sgi
Sgi_t sgi;
/*
    function definition
*/
bool sgi_Key_Down(int key);
bool sgi_Init(int w, int h, char *title);
int sgi_Mode_None();
int sgi_Mode_Blend();
int sgi_Mode_Add();
int sgi_Mode_Mod();
void sgi_Update();
void sgi_ReadKeys();
void sgi_GetMouseState(int *x, int *y);
unsigned long sgi_GetTicks();
void sgi_Delay(int ms);
bool sgi_Done(void);
void sgi_Fini();
void sgi_Clear(RGBA col);
void sgi_Point(int x, int y, RGBA col);
bool sgi_Line(int x1, int y1, int x2, int y2, RGBA col);
bool sgi_Circle(int xc, int yc, int radius, RGBA col);
bool sgi_Disk(int xc, int yc, int radius, RGBA col);
bool sgi_Rect(int x, int y, int w, int h, RGBA col);
bool sgi_FillRect(int x, int y, int w, int h, RGBA col);
////////////////////////////////////////////////////
bool sgi_Key_Down(int key) {
  if (!sgi.inkeys)
    return false;
  return (sgi.inkeys[key] != 0);
}
/*
    Initialized BGI...
*/
bool sgi_Init(int w, int h, char *title) {
  // Initialization flag

  bool bRet = true;
  sgi.w = w;
  sgi.h = h;
  SDL_SetMainReady();

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    bRet = false;
    return bRet;
  };
  sgi.Window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       w, h, SDL_WINDOW_SHOWN);
  if (sgi.Window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    bRet = false;
    return bRet;
  };
  sgi.Renderer = SDL_CreateRenderer(sgi.Window, -1, SDL_RENDERER_ACCELERATED);
  if (sgi.Renderer == NULL) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    bRet = false;
    return bRet;
  };
  return bRet;
}
////////////////////////////////////////////////////////////////////////////////////
int sgi_Mode_None() {
  return SDL_SetRenderDrawBlendMode(sgi.Renderer, SDL_BLENDMODE_NONE);
}
////////////////////////////////////////////////////////////////////////////////////
int sgi_Mode_Blend() {
  return SDL_SetRenderDrawBlendMode(sgi.Renderer, SDL_BLENDMODE_BLEND);
}
////////////////////////////////////////////////////////////////////////////////////
int sgi_Mode_Add() {
  return SDL_SetRenderDrawBlendMode(sgi.Renderer, SDL_BLENDMODE_ADD);
}
////////////////////////////////////////////////////////////////////////////////////
int sgi_Mode_Mod() {
  return SDL_SetRenderDrawBlendMode(sgi.Renderer, SDL_BLENDMODE_MOD);
}
////////////////////////////////////////////////////////////////////////////////////
void sgi_Update() { SDL_RenderPresent(sgi.Renderer); }
///////////////////////////////////////////////////////////////////
// sdl input function ...
///////////////////////////////////////////////////////////////////
void sgi_ReadKeys() {
  SDL_PumpEvents();
  sgi.inkeys = SDL_GetKeyboardState(NULL);
}
////////////////////////////////////////////////////////////////////////////////////
void sgi_GetMouseState(int *x, int *y) {
  uint8_t mouseState = SDL_GetMouseState(&sgi.mouseX, &sgi.mouseY);
  *x = sgi.mouseX;
  *y = sgi.mouseY;
  if (mouseState & 1)
    sgi.LMB = true;
  else
    sgi.LMB = false;
  if (mouseState & 4)
    sgi.RMB = true;
  else
    sgi.RMB = false;
}
// Returns the time in milliseconds since the program started
unsigned long sgi_GetTicks() { return SDL_GetTicks(); }
//////////////////////////////////////////////////////////////////////
void sgi_Delay(int ms) { SDL_Delay(ms); }
////////////////////////////////////////////////////////////////////////////////////
bool sgi_Done(void) {
  while (SDL_PollEvent(&sgi.event)) {
    if (sgi.event.type == SDL_QUIT)
      return true;
  }
  sgi_ReadKeys();
  if (sgi.inkeys[SDL_SCANCODE_ESCAPE])
    return true;
  return false;
}
////////////////////////////////////////////////////////////////////////////////////
void sgi_Fini() {
  SDL_DestroyRenderer(sgi.Renderer);
  sgi.Renderer = NULL;
  SDL_DestroyWindow(sgi.Window);
  sgi.Window = NULL;
  SDL_Quit();
}
////////////////////////////////////////////////////////////////////////////////////
void sgi_Clear(RGBA col) {
  if (col.color != sgi.SelColor.color) {
    sgi.SelColor.color = col.color;
    SDL_SetRenderDrawColor(sgi.Renderer, col.r, col.g, col.b, col.a);
  }
  SDL_RenderClear(sgi.Renderer);
}
////////////////////////////////////////////////////////////////////////////////////
void sgi_Point(int x, int y, RGBA col) {
  if (col.color != sgi.SelColor.color) {
    sgi.SelColor.color = col.color;
    SDL_SetRenderDrawColor(sgi.Renderer, col.r, col.g, col.b, col.a);
  }
  SDL_RenderDrawPoint(sgi.Renderer, x, y);
}
////////////////////////////////////////////////////////////////////////////////////
bool sgi_Line(int x1, int y1, int x2, int y2, RGBA col) {
  if (x1 < 0 || x1 > sgi.w - 1 || x2 < 0 || x2 > sgi.w - 1 || y1 < 0 ||
      y1 > sgi.h - 1 || y2 < 0 || y2 > sgi.h - 1)
    return false;
  if (col.color != sgi.SelColor.color) {
    sgi.SelColor.color = col.color;
    SDL_SetRenderDrawColor(sgi.Renderer, col.r, col.g, col.b, col.a);
  }
  SDL_RenderDrawLine(sgi.Renderer, x1, y1, x2, y2);
  return true;
}
////////////////////////////////////////////////////////////////////////////
// Bresenham circle with center at(xc, yc) with radius and red green blue color
bool sgi_Circle(int xc, int yc, int radius, RGBA col) {
  if (xc - radius < 0 || xc + radius >= sgi.w || yc - radius < 0 ||
      yc + radius >= sgi.h)
    return false;
  if (col.color != sgi.SelColor.color) {
    sgi.SelColor.color = col.color;
    SDL_SetRenderDrawColor(sgi.Renderer, col.r, col.g, col.b, col.a);
  }
  int x = 0;
  int y = radius;
  int p = 3 - (radius << 1);
  int a, b, c, d, e, f, g, h;
  while (x <= y) {
    a = xc + x; // 8 pixels can be calculated at once thanks to the symmetry
    b = yc + y;
    c = xc - x;
    d = yc - y;
    e = xc + y;
    f = yc + x;
    g = xc - y;
    h = yc - x;
    SDL_RenderDrawPoint(sgi.Renderer, a, b);
    SDL_RenderDrawPoint(sgi.Renderer, c, d);
    SDL_RenderDrawPoint(sgi.Renderer, e, f);
    SDL_RenderDrawPoint(sgi.Renderer, g, f);
    if (x > 0) { // avoid drawing pixels at same position as the other ones
      SDL_RenderDrawPoint(sgi.Renderer, a, d);
      SDL_RenderDrawPoint(sgi.Renderer, c, b);
      SDL_RenderDrawPoint(sgi.Renderer, e, h);
      SDL_RenderDrawPoint(sgi.Renderer, g, h);
    }
    if (p < 0)
      p += (x++ << 2) + 6;
    else
      p += ((x++ - y--) << 2) + 10;
  }
  return true;
}
///////////////////////////////////////////////////////////////////////////////
// Filled bresenham circle with center at (xc,yc) with radius and red green blue
// color
bool sgi_Disk(int xc, int yc, int radius, RGBA col) {
  if (xc + radius < 0 || xc - radius >= sgi.w || yc + radius < 0 ||
      yc - radius >= sgi.h)
    return false; // every single pixel outside screen, so don't waste time on
  // it
  if (col.color != sgi.SelColor.color) {
    sgi.SelColor.color = col.color;
    SDL_SetRenderDrawColor(sgi.Renderer, col.r, col.g, col.b, col.a);
  }
  int x = 0;
  int y = radius;
  int p = 3 - (radius << 1);
  int a, b, c, d, e, f, g, h;
  int pb = yc + radius + 1,
      pd = yc + radius + 1; // previous values: to avoid drawing horizontal
  // lines multiple times
  // (ensure initial value is outside the range)
  while (x <= y) {
    // write data
    a = xc + x;
    b = yc + y;
    c = xc - x;
    d = yc - y;
    e = xc + y;
    f = yc + x;
    g = xc - y;
    h = yc - x;
    if (b != pb)
      SDL_RenderDrawLine(sgi.Renderer, a, b, c, b);
    if (d != pd)
      SDL_RenderDrawLine(sgi.Renderer, a, d, c, d);
    if (f != b)
      SDL_RenderDrawLine(sgi.Renderer, e, f, g, f);
    if (h != d && h != f)
      SDL_RenderDrawLine(sgi.Renderer, e, h, g, h);
    pb = b;
    pd = d;
    if (p < 0)
      p += (x++ << 2) + 6;
    else
      p += ((x++ - y--) << 2) + 10;
  }
  return true;
}
bool sgi_Rect(int x, int y, int w, int h, RGBA col) {
  if (x < 0 || x > sgi.w - 1 || x + w > sgi.w - 1 || y < 0 || y > sgi.h - 1 ||
      y + h > sgi.h - 1)
    return false;
  if (col.color != sgi.SelColor.color) {
    sgi.SelColor.color = col.color;
    SDL_SetRenderDrawColor(sgi.Renderer, col.r, col.g, col.b, col.a);
  }
  SDL_Rect rect;
  rect.h = h;
  rect.w = w;
  rect.x = x;
  rect.y = y;
  SDL_RenderDrawRect(sgi.Renderer, &rect);
  return true;
}
bool sgi_FillRect(int x, int y, int w, int h, RGBA col) {
  if (x < 0 || x > sgi.w - 1 || x + w > sgi.w - 1 || y < 0 || y > sgi.h - 1 ||
      y + h > sgi.h - 1)
    return false;
  if (col.color != sgi.SelColor.color) {
    sgi.SelColor.color = col.color;
    SDL_SetRenderDrawColor(sgi.Renderer, col.r, col.g, col.b, col.a);
  }
  SDL_Rect rect;
  rect.h = h;
  rect.w = w;
  rect.x = x;
  rect.y = y;
  SDL_RenderFillRect(sgi.Renderer, &rect);
  return true;
}
/////////////////////////////////////////////////////////////////////////////////////
/*
SGI Image
*/
typedef struct sgi_Image {
  SDL_Texture *Tex;
  int w, h;
  void (*Boundary)(struct sgi_Image *self, int *w, int *h);
  void (*Draw)(struct sgi_Image *simg, int x, int y, float angle);
  void (*Destroy)(struct sgi_Image *self);
} sgi_Image;

static void _sgi_image_destroy(sgi_Image *simg) {
  if (simg != NULL) {
    SDL_DestroyTexture(simg->Tex);
    free(simg);
    simg = NULL;
  }
}
static void _boundary(sgi_Image *simg, int *w, int *h) {
  *w = simg->w;
  *h = simg->h;
}
static void _draw(sgi_Image *simg, int x, int y, float angle) {
  SDL_Rect src = {0, 0, simg->w, simg->h};
  SDL_Rect dest = {x - simg->w / 2, y - simg->h / 2, simg->w, simg->h};
  SDL_RenderCopyEx(sgi.Renderer, simg->Tex, &src, &dest, angle, NULL,
                   SDL_FLIP_NONE);
}
sgi_Image *NewSgiImage(char *filename) {
  sgi_Image *simg = (sgi_Image *)malloc(sizeof(sgi_Image));
  SDL_Surface *surface = SDL_LoadBMP(filename);
  if (!surface) {
    return NULL;
  }
  SDL_SetColorKey(surface, SDL_TRUE, 0);
  simg->w = surface->w;
  simg->h = surface->h;
  simg->Tex = SDL_CreateTextureFromSurface(sgi.Renderer, surface);
  SDL_FreeSurface(surface);
  SDL_SetTextureBlendMode(simg->Tex, SDL_BLENDMODE_BLEND);
  simg->Boundary = &_boundary;
  simg->Draw = &_draw;
  simg->Destroy = &_sgi_image_destroy;
  return simg;
}
#endif // header guard
