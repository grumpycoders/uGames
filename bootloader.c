#include <stdlib.h>

#include "uGL/uGL.h"

int main()
{
  uGL_init();

  uGL_color_t gradientcolor = { .r = 0, .g = 0, .b = 0 };
  for (int i = 0 ; i < 256 ; i++)
  {
    gradientcolor.g = i;
    uGL_drawPixel(10, i, gradientcolor);
  }

  uGL_color_t backgroundcolor = { .r = 70, .g = 120, .b = 240 };
  uGL_drawRectangle(0, 0, 240, 320, backgroundcolor);

  uGL_color_t rectcolor = { .r = 250, .g = 120, .b = 40 };
  uGL_drawRectangle(50, 100, 100, 200, rectcolor);

  uGL_color_t hlinecolor = { .r = 50, .g = 240, .b = 40 };
  uGL_drawHLine(20, 50, 100, hlinecolor);

  uGL_color_t vlinecolor = { .r = 250, .g = 240, .b = 40 };
  uGL_drawVLine(50, 20, 200, vlinecolor);

  while(1);
  return 0;
}
