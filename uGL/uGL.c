#include "uGL.h"

#include <string.h>

#include "stm32f429i_discovery_lcd.h"
#include <stm32f4xx_ltdc.h>

static uint16_t *_framebuffer = (uint16_t *)(LCD_FRAME_BUFFER + BUFFER_OFFSET);
static const uint16_t screenwidth = 240;
static const  uint16_t screenheight = 320;

void uGL_init()
{
  LCD_Init();

  LCD_LayerInit();
  LTDC_Cmd(ENABLE);

//  LCD_SetFont(&Font8x8);
//  LCD_SetLayer(LCD_BACKGROUND_LAYER);
//    LCD_Clear(ASSEMBLE_RGB(0x00, 0x66, 0x00));
  LCD_SetLayer(LCD_FOREGROUND_LAYER);
//  LCD_SetBackColor(ASSEMBLE_RGB(0x00, 0x00, 0xFF));
}


uint16_t uGL_getScreenHeight()
{
  return screenheight;
}

uint16_t uGL_getScreenWidth()
{
  return screenwidth;
}

void uGL_drawPixel(uint16_t x, uint16_t y, uGL_color_t color)
{
  _framebuffer[x + screenwidth * y] = ASSEMBLE_RGB2(color);
}

void uGL_drawHLine(uint16_t x, uint16_t y, uint16_t length, uGL_color_t color)
{
  for (int i = 0 ; i < length ; i++)
    uGL_drawPixel(x + i, y, color);
}

void uGL_drawVLine(uint16_t x, uint16_t y, uint16_t length, uGL_color_t color)
{
  LCD_SetTextColor(ASSEMBLE_RGB2(color));
  for (int i = 0 ; i < length ; i++)
    uGL_drawPixel(x, y + i, color);
  //LCD_DrawLine(x, y, length, LCD_DIR_VERTICAL);
}

void uGL_drawFrame(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uGL_color_t color)
{
  uGL_drawHLine(x, y, width, color);
  uGL_drawHLine(x, (y + height), width, color);
  uGL_drawVLine(x, y, height, color);
  uGL_drawVLine((x + width), y, height, color);
}

void uGL_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uGL_color_t color)
{
  LCD_SetTextColor(ASSEMBLE_RGB2(color));
//  LCD_SetTextColor(color);
  //LCD_SetTextColor(ASSEMBLE_RGB(color.r, color.g, color.b));
  LCD_DrawFullRect(x, y, width, height);
}

void uGl_blitImage(uGL_image_t *image, uint16_t x, uint16_t y)
{
}
