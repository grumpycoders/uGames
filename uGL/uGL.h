#pragma once

#include <stdlib.h>

typedef union {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} uGL_color_t;

typedef uGL_color_t *uGL_lookuptable;

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
  uint16_t length;
  uGL_colormode colormode;
  uGL_lookuptable *lookuptable;
  uint8_t *data;
} uGL_image_t;


void uGL_init();

uint16_t uGL_getScreenHeight();
uint16_t uGL_getScreenWidth();

void uGL_drawPixel(uint16_t x, uint16_t y, uGL_color_t color);
void uGL_drawHLine(uint16_t x, uint16_t y, uint16_t length, uGL_color_t color);
void uGL_drawVLine(uint16_t x, uint16_t y, uint16_t length, uGL_color_t color);
void uGL_drawFrame(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uGL_color_t color);
void uGL_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uGL_color_t color);

void uGl_blitImage(uGL_image_t *image, uint16_t x, uint16_t y);
