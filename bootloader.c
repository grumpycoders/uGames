#include <stdlib.h>

#include "uGL/uGL.h"

void drawRainbow()
{
  uGL_color_t c;
  for (uint16_t i = 0 ; i < 40 ; i++)
  {
    //rouge => jaune
    c.r = 0xff; c.g = i * 0xff / 40; c.b = 0x00;
    uGL_drawVLine(i, 0, 10, c);
    //jaune => vert
    c.r = 0xff - i * 0xff / 40; c.g = 0xff; c.b = 0x00;
    uGL_drawVLine(i + 40, 0, 10, c);
    //vert => cyan
    c.r = 0x00; c.g = 0xff; c.b = i * 0xff / 40;
    uGL_drawVLine(i + 80, 0, 10, c);
    //cyan => bleu
    c.r = 0x00; c.g = 0xff - i * 0xff / 40; c.b = 0xff;
    uGL_drawVLine(i + 120, 0, 10, c);
    //bleu => violet
    c.r = i * 0xff / 40; c.g = 0x00; c.b = 0xff;
    uGL_drawVLine(i + 160, 0, 10, c);
    //violet => rouge
    c.r = 0xff; c.g = 0x00; c.b = 0xff - i * 0xff / 40;
    uGL_drawVLine(i + 200, 0, 10, c);
  }
}

int main()
{
  uGL_init();

  uGL_color_t backgroundcolor = { .r = 255, .g = 255, .b = 255 };
  uGL_drawRectangle(0, 0, 240, 320, backgroundcolor);

  uGL_color_t black = { .r = 0, .g = 0, .b = 0 };
  for (uint8_t i = 0 ; i < 6 ; i++)
    uGL_drawHLine(0, i * 50, 240, black);

  for (uint8_t i = 0 ; i < 4 ; i++)
    uGL_drawVLine(i * 50, 0, 320, black);

  uGL_color_t gradientcolor = { .r = 0, .g = 0, .b = 0 };
  for (uint8_t i = 0 ; i < 255 ; i++)
  {
    gradientcolor.g = i;
    uGL_drawPixel(10, i, gradientcolor);
    uGL_drawHLine(20, i, 10, gradientcolor);
  }

  drawRainbow();

  uGL_color_t rectcolor = { .r = 250, .g = 120, .b = 10 };
  uGL_drawFrame(10, 30, 100, 50, rectcolor);

  uGL_color_t hlinecolor = { .r = 50, .g = 240, .b = 20 };
  uGL_drawHLine(120, 80, 100, hlinecolor);

  uGL_color_t vlinecolor = { .r = 250, .g = 240, .b = 10 };
  uGL_drawVLine(90, 20, 200, vlinecolor);

  while(1);
  return 0;
}
