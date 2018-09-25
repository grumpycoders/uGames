#include <stdlib.h>

#include "uGL/uGL.h"

int main()
{
  uGL_init();

  uGL_color_t backgroundcolor = { .r = 255, .g = 255, .b = 255 };
  uGL_drawRectangle(0, 0, 240, 320, backgroundcolor);

  uGL_color_t gradientcolor = { .r = 0, .g = 0, .b = 0 };
  for (uint8_t i = 0 ; i < 255 ; i++)
  {
    gradientcolor.g = i;
    uGL_drawPixel(10, i, gradientcolor);
    uGL_drawHLine(20, i, 10, gradientcolor);
  }

  uGL_color_t black = { .r = 0, .g = 0, .b = 0 };
  for (uint8_t i = 0 ; i < 6 ; i++)
    uGL_drawHLine(0, i * 50, 240, black);

  for (uint8_t i = 0 ; i < 4 ; i++)
    uGL_drawVLine(i * 50, 0, 320, black);

  uGL_color_t rectcolor = { .r = 250, .g = 120, .b = 10 };
  uGL_drawFrame(10, 30, 100, 50, rectcolor);

  uGL_color_t hlinecolor = { .r = 50, .g = 240, .b = 20 };
  uGL_drawHLine(20, 50, 100, hlinecolor);

  uGL_color_t vlinecolor = { .r = 250, .g = 240, .b = 10 };
  uGL_drawVLine(50, 20, 200, vlinecolor);

  while(1);
  return 0;
}
