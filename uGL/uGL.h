#pragma once

#include <stdlib.h>

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} uGL_color_rgba_t;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} uGL_color_rgb_t;

typedef uint8_t uGL_color_indexed_t;

typedef enum {
  INDEXED1 = 1,
  INDEXED2 = 2,
  INDEXED4 = 4,
  INDEXED8 = 8,
  RGB      = 24,
  RGBA     = 32
} uGL_colormode;

typedef struct {
  uint16_t width;
  uint16_t height;
  uGL_colormode colormode;
  union {
    uGL_color_rgb_t *rgb;
    uGL_color_rgba_t *rgba;
    uGL_color_indexed_t *indexed;
  } data;
} uGL_image_t;

typedef uGL_color_rgb_t *uGL_lookuptable;

typedef struct {
  uint8_t id;
  uGL_image_t *pixels;
} uGL_sprite_t;


void uGL_init();

void uGL_displayOn();
void uGL_displayOff();

uint16_t uGL_getScreenHeight();
uint16_t uGL_getScreenWidth();
/*
void uGL_drawPixel(uint16_t x, uint16_t y, uGL_color_t color);
void uGL_drawHLine(uint16_t x, uint16_t y, uint16_t length, uGL_color_t color);
void uGL_drawVLine(uint16_t x, uint16_t y, uint16_t length, uGL_color_t color);
void uGL_drawFrame(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uGL_color_t color);
void uGL_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uGL_color_t color);

void uGl_drawImage(uGL_image_t *image, uint16_t x, uint16_t y);
*/
void uGL_drawText(uint16_t x, uint16_t y, uint8_t font, char *text, uint8_t nb, uGL_color_rgb_t color);

void uGl_loadSprite(uGL_sprite_t *sprite);
void uGl_unloadSprite(uGL_sprite_t *sprite);
void uGl_drawSprite(uGL_sprite_t *sprite, uint16_t x, uint16_t y);

void uGl_setLookupTable(uGL_colormode bitspercolor, uGL_color_rgb_t *colors);
