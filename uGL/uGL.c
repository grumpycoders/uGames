#include "uGL.h"

#include "stm32f429i_discovery_lcd.h"
#include <stm32f4xx_ltdc.h>

void uGL_init()
{
  LCD_Init();

  LCD_LayerInit();
  LTDC_Cmd(ENABLE);

  LCD_SetFont(&Font8x8);
  LCD_SetLayer(LCD_BACKGROUND_LAYER);
//    LCD_Clear(ASSEMBLE_RGB(0x00, 0x66, 0x00));
  LCD_SetLayer(LCD_FOREGROUND_LAYER);
  LCD_SetBackColor(ASSEMBLE_RGB(0x00, 0x00, 0xFF));
}

void uGL_drawPixel(uint16_t x, uint16_t y, uGL_color_t color)
{
  LCD_SetTextColor(ASSEMBLE_RGB(color.r, color.g, color.b));
//  PutPixel(int16_t x, int16_t y);
}

void uGL_drawHLine(uint16_t x, uint16_t y, uint16_t length, uGL_color_t color)
{
  LCD_SetTextColor(ASSEMBLE_RGB(color.r, color.g, color.b));
  LCD_DrawLine(x, y, length, LCD_DIR_HORIZONTAL);
}

void uGL_drawVLine(uint16_t x, uint16_t y, uint16_t length, uGL_color_t color)
{
  LCD_SetTextColor(ASSEMBLE_RGB(color.r, color.g, color.b));
  LCD_DrawLine(x, y, length, LCD_DIR_VERTICAL);
}

void uGL_drawFrame(uint16_t x, uint16_t y, uint16_t width, uint16_t length, uGL_color_t color)
{
  LCD_SetTextColor(ASSEMBLE_RGB(color.r, color.g, color.b));
  LCD_DrawRect(x, y, width, length);
}

void uGL_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t length, uGL_color_t color)
{
  LCD_SetTextColor(ASSEMBLE_RGB(color.r, color.g, color.b));
  LCD_DrawFullRect(x, y, width, length);
}

void uGl_blitImage(uGL_image_t *image, uint16_t x, uint16_t y)
{
}
