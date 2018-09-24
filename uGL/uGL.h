#pragma once

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} uGL_color;

typedef uGL_color *uGL_lookuptable;

typedef enum {
  INDEXED1  1,
  INDEXED2  2,
  INDEXED4  4,
  INDEXED8  8,
  RGB      24,
  RGBA     32
} uGL_colormode;

typedef struct {
  uint16_t width;
  uint16_t length;
  uGL_colormode colormode;
  uGL_lookuptable *lookuptable;
  uint8_t *data;
} uGL_image;


uGL_init();

uGL_drawPixel(uint16_t x, uint16_t y, uGL_color color);
uGL_drawHLine(uint16_t x, uint16_t y, uint16_t length, uGL_color color);
uGL_drawVLine(uint16_t x, uint16_t y, uint16_t length, uGL_color color);
uGL_drawFrame(uint16_t x, uint16_t y, uint16_t width, uint16_t length, uGL_color color);
uGL_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t length, uGL_color color);

uGl_blitImage(uGL_image image, uint16_t x, uint16_t y);
