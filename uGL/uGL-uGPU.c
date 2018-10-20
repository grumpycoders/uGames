#include "uGL.h"

#include <math.h>

#include <gpio.h>
#include <ssp.h>

pin_t cs;

#define SSP ssp_4
#define SPRITE_SIZE (16*16)

void ssp_write_uint16(uint16_t v) {
  ssp_write(SSP, (uint8_t)(v >> 8));
  ssp_write(SSP, (uint8_t)(v & 0x00ff));
}

void uGL_init() {
  pin_t sck = make_pin(gpio_port_e, 2);
  pin_t miso = make_pin(gpio_port_e, 5);
  pin_t mosi = make_pin(gpio_port_e, 6);
  ssp_port_t ssp = {
  	.sclk = sck,
  	.mosi = mosi,
  	.miso = miso,
  	.ss = PIN_NULL,
  	.mode = ssp_master,
  	.polarity = ssp_polarity_mode_0,
  	.ssp = ssp_4
  };
  ssp_config(ssp, 8000000);

  cs = make_pin(gpio_port_d, 1);

  gpio_config(cs, pin_dir_write, pull_none);
  gpio_set(cs, 1);

  gpio_set(cs, 0);
  ssp_write(SSP, 's');
  ssp_write_uint16((uint16_t) 480);
  ssp_write_uint16((uint16_t) 272);
  gpio_set(cs, 1);

  uGL_displayOn();
}

void uGL_displayOn() {
  gpio_set(cs, 0);
  ssp_write(SSP, 'o');
  gpio_set(cs, 1);
}

void uGL_displayOff() {
  gpio_set(cs, 0);
  ssp_write(SSP, 'f');
  gpio_set(cs, 1);
}

void uGL_drawText(uint16_t x, uint16_t y, uint8_t font, char *text, uint8_t nb, uGL_color_rgb_t color) {
  for (uint8_t i = 0 ; i < nb ; i++) {
    gpio_set(cs, 0);
    ssp_write(SSP, 't');
    ssp_write(SSP, font);
    ssp_write(SSP, text[i]);
    ssp_write_uint16(x + i * font);
    ssp_write_uint16(y);
    ssp_write(SSP, color.r);
    ssp_write(SSP, color.g);
    ssp_write(SSP, color.b);
    gpio_set(cs, 1);
  }
}

void uGl_loadSprite(uGL_sprite_t *sprite) {
  //check image size?
  //do we assume it is RGB? RGBA?
  gpio_set(cs, 0);
  ssp_write(SSP, 'l');
  ssp_write(SSP, sprite->id);
  for (unsigned i = 0 ; i < SPRITE_SIZE ; i++) {
    ssp_write(SSP, sprite->pixels->data.rgb[i].r);
    ssp_write(SSP, sprite->pixels->data.rgb[i].g);
    ssp_write(SSP, sprite->pixels->data.rgb[i].b);
  }
  gpio_set(cs, 1);
}

void uGl_unloadSprite(uGL_sprite_t *sprite) {
  gpio_set(cs, 0);
  ssp_write(SSP, 'u');
  ssp_write(SSP, sprite->id);
  gpio_set(cs, 1);
}

void uGl_drawSprite(uGL_sprite_t *sprite, uint16_t x, uint16_t y) {
  gpio_set(cs, 0);
  ssp_write(SSP, 'd');
  ssp_write_uint16((uint16_t) x);
  ssp_write_uint16((uint16_t) y);
  gpio_set(cs, 1);
}

void uGl_setLookupTable(uGL_colormode bitspercolor, uGL_color_rgb_t *colors) {
  gpio_set(cs, 0);
  ssp_write(SSP, 'i');
  ssp_write(SSP, bitspercolor);
  for (uint8_t i = 0 ; i < pow(2, bitspercolor) ; i++) {
    ssp_write(SSP, colors[i].r);
    ssp_write(SSP, colors[i].g);
    ssp_write(SSP, colors[i].b);
  }
  gpio_set(cs, 1);
}
