#ifndef __SSD1306_H__
#define __SSD1306_H__

#include "hdr.h"

#ifdef SET_SSD1306

#define FONT_WIDTH 8
#define OLED_WIDTH 128

#ifdef OLED_128x32
    #define OLED_MAX_STR 4
#else
    #define OLED_MAX_STR 8
#endif
#define OLED_LINE_FREQ OLED_MAX_STR
#define OLED_LINE_CENTER (OLED_MAX_STR >> 1)
#define OLED_LINE_STEP OLED_MAX_STR - 1

// SLA (0x3C) + WRITE_MODE (0x00) =  0x78 (0b01111000)
#define OLED_I2C_ADDRESS   0x3C

// Control byte
#define OLED_CONTROL_BYTE_CMD_SINGLE    0x80
#define OLED_CONTROL_BYTE_CMD_STREAM    0x00
#define OLED_CONTROL_BYTE_DATA_STREAM   0x40

// Fundamental commands (pg.28)
#define OLED_CMD_SET_CONTRAST           0x81    // follow with 0x7F
#define OLED_CMD_DISPLAY_RAM            0xA4
#define OLED_CMD_DISPLAY_ALLON          0xA5
#define OLED_CMD_DISPLAY_NORMAL         0xA6
#define OLED_CMD_DISPLAY_INVERTED       0xA7
#define OLED_CMD_DISPLAY_OFF            0xAE
#define OLED_CMD_DISPLAY_ON             0xAF

// Addressing Command Table (pg.30)
#define OLED_CMD_SET_MEMORY_ADDR_MODE   0x20    // follow with 0x00 = HORZ mode = Behave like a KS108 graphic LCD
#define OLED_CMD_SET_COLUMN_RANGE       0x21    // can be used only in HORZ/VERT mode - follow with 0x00 and 0x7F = COL127
#define OLED_CMD_SET_PAGE_RANGE         0x22    // can be used only in HORZ/VERT mode - follow with 0x00 and 0x07 = PAGE7

#define OLED_CMD_SET_DEACTIVATE_SCROLL  0x2E
#define OLED_CMD_SET_ACTIVATE_SCROLL    0x2F

// Hardware Config (pg.31)
#define OLED_CMD_SET_DISPLAY_START_LINE 0x40
#define OLED_CMD_SET_SEGMENT_REMAP      0xA1
#define OLED_CMD_SET_MUX_RATIO          0xA8    // follow with 0x3F = 64 MUX or 1F = 32 MUX
#define OLED_CMD_SET_COM_SCAN_MODE      0xC8
#define OLED_CMD_SET_DISPLAY_OFFSET     0xD3    // follow with 0x00
#define OLED_CMD_SET_COM_PIN_MAP        0xDA    // follow with 0x12
#define OLED_CMD_NOP                    0xE3    // NOP

// Timing and Driving Scheme (pg.32)
#define OLED_CMD_SET_DISPLAY_CLK_DIV    0xD5    // follow with 0x80
#define OLED_CMD_SET_PRECHARGE          0xD9    // follow with 0xF1
#define OLED_CMD_SET_VCOMH_DESELCT      0xDB    // follow with 0x30

// Charge Pump (pg.62)
#define OLED_CMD_SET_CHARGE_PUMP        0x8D    // follow with 0x14



extern xSemaphoreHandle lcd_mutex;


esp_err_t ssd1306_on(bool flag);
void i2c_ssd1306_init();
esp_err_t ssd1306_init();
void ssd1306_invert();
void ssd1306_clear();
void ssd1306_clear_lines(uint8_t cy, uint8_t cnt);
//void ssd1306_clear_line(uint8_t cy);
void ssd1306_pattern();
void ssd1306_contrast(uint8_t value);
void ssd1306_shift(bool left, uint8_t line);
void ssd1306_scroll(bool flag);
void ssd1306_text_xy(const char *stroka, uint8_t cx, uint8_t cy, bool inv);
void ssd1306_text(const char *stroka);
uint8_t ssd1306_calcx(int len);
char *mkLineCenter(char *str, uint16_t width);
char *mkLineWidth(char *str1, char *str2, uint16_t width);

#endif

#endif

