#include "uGL.h"

#include <string.h>

//#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"

#include <gpio.h>
#include <lcddriver.h>


/**
  * @brief  LCD Registers
  */
#define LCD_SLEEP_OUT            0x11   /* Sleep out register */
#define LCD_GAMMA                0x26   /* Gamma register */
#define LCD_DISPLAY_OFF          0x28   /* Display off register */
#define LCD_DISPLAY_ON           0x29   /* Display on register */
#define LCD_COLUMN_ADDR          0x2A   /* Colomn address register */
#define LCD_PAGE_ADDR            0x2B   /* Page address register */
#define LCD_GRAM                 0x2C   /* GRAM register */
#define LCD_MAC                  0x36   /* Memory Access Control register*/
#define LCD_PIXEL_FORMAT         0x3A   /* Pixel Format register */
#define LCD_WDB                  0x51   /* Write Brightness Display register */
#define LCD_WCD                  0x53   /* Write Control Display register*/
#define LCD_RGB_INTERFACE        0xB0   /* RGB Interface Signal Control */
#define LCD_FRC                  0xB1   /* Frame Rate Control register */
#define LCD_BPC                  0xB5   /* Blanking Porch Control register*/
#define LCD_DFC                  0xB6   /* Display Function Control register*/
#define LCD_POWER1               0xC0   /* Power Control 1 register */
#define LCD_POWER2               0xC1   /* Power Control 2 register */
#define LCD_VCOM1                0xC5   /* VCOM Control 1 register */
#define LCD_VCOM2                0xC7   /* VCOM Control 2 register */
#define LCD_POWERA               0xCB   /* Power control A register */
#define LCD_POWERB               0xCF   /* Power control B register */
#define LCD_PGAMMA               0xE0   /* Positive Gamma Correction register*/
#define LCD_NGAMMA               0xE1   /* Negative Gamma Correction register*/
#define LCD_DTCA                 0xE8   /* Driver timing control A */
#define LCD_DTCB                 0xEA   /* Driver timing control B */
#define LCD_POWER_SEQ            0xED   /* Power on sequence register */
#define LCD_3GAMMA_EN            0xF2   /* 3 Gamma enable register */
#define LCD_INTERFACE            0xF6   /* Interface control register */
#define LCD_PRC                  0xF7   /* Pump ratio control register */


static uint16_t *_framebuffer = (uint16_t *)(0xD0000000 + 0x50000);
static const uint16_t screenwidth = 240;
static const  uint16_t screenheight = 320;

#include <gpio.h>
#include <ssp.h>
ssp_port_t lcd_port = {
    .ssp = ssp_5,
    .sclk = { .port = gpio_port_f, .pin = 7 },
    .mosi = { .port = gpio_port_f, .pin = 9 },
    .miso = { .port = gpio_port_f, .pin = 8 },
    .ss = PIN_NULL,
    .mode = ssp_master
  };
pin_t lcd_ncs = { .port = gpio_port_c, .pin = 2 };
pin_t lcd_wrx = { .port = gpio_port_d, .pin = 13 };

#define ASSEMBLE_RGB2(RGB)    ((((RGB.r) & 0xF8) << 8) | (((RGB.g) & 0xFC) << 3) | (((RGB.b) & 0xF8) >> 3))

void uGL_writeChunk(uint8_t *data, uint8_t nb)
{
  if (nb < 1) return;
  gpio_set(lcd_wrx, 0);
  gpio_set(lcd_ncs, 0);
  ssp_write(ssp_5, data[0]);
  while(SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_BSY) != RESET);

  for (int i = 1 ; i < nb ; i++)
  {
    gpio_set(lcd_wrx, 1);
    ssp_write(ssp_5, data[i]);
    while(SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_BSY) != RESET);
  }
  gpio_set(lcd_ncs, 1);
}

#ifndef USE_Delay
/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void delay(__IO uint32_t nCount)
{
  __IO uint32_t index = 0;
  for(index = nCount; index != 0; index--)
  {
  }
}
#endif

void uGL_init_sequence() {

  uint8_t buffer_init[] = {0xCA, 0xC3, 0x08, 0x50};
  uGL_writeChunk(buffer_init, 4);

  uint8_t buffer_powerb[] = {LCD_POWERB, 0x00, 0xC1, 0x30};
  uGL_writeChunk(buffer_powerb, 4);

  uint8_t buffer_powerseq[] = {LCD_POWER_SEQ, 0x64, 0x03, 0x12, 0x81};
  uGL_writeChunk(buffer_powerseq, 5);

  uint8_t buffer_dtca[] = {LCD_DTCA, 0x85, 0x00, 0x78};
  uGL_writeChunk(buffer_dtca, 4);

  uint8_t buffer_powera[] = {LCD_DTCA, 0x39, 0x2C, 0x00, 0x34, 0x02};
  uGL_writeChunk(buffer_powera, 6);

  uint8_t buffer_prc[] = {LCD_PRC, 0x20};
  uGL_writeChunk(buffer_prc, 2);

  uint8_t buffer_dtcb[] = {LCD_DTCB, 0x00, 0x00};
  uGL_writeChunk(buffer_dtcb, 3);

  uint8_t buffer_frc[] = {LCD_FRC, 0x00, 0x1B};
  uGL_writeChunk(buffer_frc, 3);

  uint8_t buffer_dfc[] = {LCD_DFC, 0x0A, 0xA2};
  uGL_writeChunk(buffer_dfc, 3);

  uint8_t buffer_power1[] = {LCD_POWER1, 0x10};
  uGL_writeChunk(buffer_power1, 2);

  uint8_t buffer_power2[] = {LCD_POWER2, 0x10};
  uGL_writeChunk(buffer_power2, 2);

  uint8_t buffer_vcom1[] = {LCD_VCOM1, 0x45, 0x15};
  uGL_writeChunk(buffer_vcom1, 3);

  uint8_t buffer_vcom2[] = {LCD_VCOM2, 0x90};
  uGL_writeChunk(buffer_vcom2, 2);

  uint8_t buffer_mac[] = {LCD_MAC, 0xC8};
  uGL_writeChunk(buffer_mac, 2);

  uint8_t buffer_3gammaen[] = {LCD_3GAMMA_EN, 0x00};
  uGL_writeChunk(buffer_3gammaen, 2);

  uint8_t buffer_rgbinterface[] = {LCD_RGB_INTERFACE, 0xc2};
  uGL_writeChunk(buffer_rgbinterface, 2);

  uint8_t buffer_dfc2[] = {LCD_DFC, 0x0A, 0xA7, 0x27, 0x04};
  uGL_writeChunk(buffer_dfc2, 5);

  uint8_t buffer_coladdr[] = {LCD_COLUMN_ADDR, 0x00, 0x00, 0x00, 0xEF};
  uGL_writeChunk(buffer_coladdr, 5);

  uint8_t buffer_pageaddr[] = {LCD_PAGE_ADDR, 0x00, 0x00, 0x01, 0x3F};
  uGL_writeChunk(buffer_pageaddr, 5);

  uint8_t buffer_interface[] = {LCD_INTERFACE, 0x01, 0x00, 0x06};
  uGL_writeChunk(buffer_interface, 4);

  uint8_t buffer_gram[] = {LCD_GRAM};
  uGL_writeChunk(buffer_gram, 1);

  delay(200);

  uint8_t buffer_gamma[] = {LCD_GAMMA, 0x01};
  uGL_writeChunk(buffer_gamma, 2);

  uint8_t buffer_pgamma[] = {LCD_PGAMMA, 0x0F, 0x29, 0x24, 0x0C, 0x0E, 0x09, 0x4E, 0x78, 0x3C, 0x09, 0x13, 0x05, 0x17, 0x11, 0x00};
  uGL_writeChunk(buffer_pgamma, 16);

  uint8_t buffer_ngamma[] = {LCD_NGAMMA, 0x00, 0x16, 0x1B, 0x04, 0x11, 0x07, 0x31, 0x33, 0x42, 0x05, 0x0C, 0x0A, 0x28, 0x2F, 0x0F};
  uGL_writeChunk(buffer_ngamma, 16);

  uint8_t buffer_sleepout[] = {LCD_SLEEP_OUT};
  uGL_writeChunk(buffer_sleepout, 1);

  delay(200);

  uint8_t buffer_displayon[] = {LCD_DISPLAY_ON};
  uGL_writeChunk(buffer_displayon, 1);

  uGL_writeChunk(buffer_gram, 1);
}

void uGL_init()
{
  //configure the LCD SPI pins
  gpio_config(lcd_ncs, pin_dir_write, pull_none);
  gpio_config(lcd_wrx, pin_dir_write, pull_none);
  gpio_set(lcd_ncs, 0);
  gpio_set(lcd_ncs, 1);
  ssp_config(lcd_port, 5600000);

  //send the init sequence to the LCD
  uGL_init_sequence();

  //clock DMA2D
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, ENABLE);

  //init LCD pins
  pin_t lcd_pin[] = {
    //r
    make_pin(gpio_port_c, 10),
    make_pin(gpio_port_b, 0),
    make_pin(gpio_port_a, 11),
    make_pin(gpio_port_a, 12),
    make_pin(gpio_port_b, 1),
    make_pin(gpio_port_g, 6),
    //g
    make_pin(gpio_port_a, 6),
    make_pin(gpio_port_g, 10),
    make_pin(gpio_port_b, 10),
    make_pin(gpio_port_b, 11),
    make_pin(gpio_port_c, 7),
    make_pin(gpio_port_d, 3),
    //b
    make_pin(gpio_port_d, 6),
    make_pin(gpio_port_g, 11),
    make_pin(gpio_port_g, 12),
    make_pin(gpio_port_a, 3),
    make_pin(gpio_port_b, 8),
    make_pin(gpio_port_b, 9),
    //hsync
    make_pin(gpio_port_c, 6),
    //vsync
    make_pin(gpio_port_a, 4),
    //clk
    make_pin(gpio_port_g, 7),
    //de
    make_pin(gpio_port_f, 10),
  };
  for (int i = 0 ; i < 22 ; i++)
    gpio_config_alternate(lcd_pin[i], pin_dir_write, pull_none, 0x0E);

  SDRAM_Init();

  lcddriver_config();
}

void uGL_displayOn()
{
  uint8_t command = LCD_DISPLAY_ON;
  uGL_writeChunk(&command, 1);
}

void uGL_displayOff()
{
  uint8_t command = LCD_DISPLAY_OFF;
  uGL_writeChunk(&command, 1);
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
  for (int i = 0 ; i < length ; i++)
    uGL_drawPixel(x, y + i, color);
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
//  LCD_SetTextColor(ASSEMBLE_RGB2(color));
//  LCD_SetTextColor(color);
  //LCD_SetTextColor(ASSEMBLE_RGB(color.r, color.g, color.b));
//  LCD_DrawFullRect(x, y, width, height);
}

void uGl_blitImage(uGL_image_t *image, uint16_t x, uint16_t y)
{
}
