#ifndef __EPD_1INCH54_H
#define __EPD_1INCH54_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "Arduino.h"

/* Pin wiring definition ESP32-C3 SuperMini
 *      3.3V --> VCC
 *      GND  --> GND
 *      GPIO7 --> CS
 *      GPIO4 --> CLK
 *      GPIO6 --> MOSI
 *      GPIO2 --> DC
 *      GPIO3 --> RST
 *      GPIO1 --> BUSY
 *      GPIO5 --> WS2812B
 */

// IO settings
#define TEST_Pin  5

#define BUSY_Pin  1
#define RES_Pin   3
#define DC_Pin    2

#define CS_Pin    7
#define SCK_Pin   4
#define SDI_Pin   6

#define TEST_0  digitalWrite(TEST_Pin,LOW)
#define TEST_1  digitalWrite(TEST_Pin,HIGH)

#define EPD_W21_MOSI_0  digitalWrite(SDI_Pin,LOW)
#define EPD_W21_MOSI_1  digitalWrite(SDI_Pin,HIGH)

#define EPD_W21_CLK_0  digitalWrite(SCK_Pin,LOW)
#define EPD_W21_CLK_1  digitalWrite(SCK_Pin,HIGH)

#define EPD_W21_CS_0   digitalWrite(CS_Pin,LOW)
#define EPD_W21_CS_1   digitalWrite(CS_Pin,HIGH)

#define EPD_W21_DC_0   digitalWrite(DC_Pin,LOW)
#define EPD_W21_DC_1   digitalWrite(DC_Pin,HIGH)
#define EPD_W21_RST_0  digitalWrite(RES_Pin,LOW)
#define EPD_W21_RST_1  digitalWrite(RES_Pin,HIGH)
#define isEPD_W21_BUSY digitalRead(BUSY_Pin)

#define MONOMSB_MODE 1
#define MONOLSB_MODE 2
#define RED_MODE     3

#define MAX_LINE_BYTES  25
#define MAX_COLUMN_BYTES  200

#define ALLSCREEN_GRAGHBYTES 5000

#define EPD_WIDTH   200
#define EPD_HEIGHT  200

void driver_delay_us(unsigned int xus);
void driver_delay_xms(unsigned long xms);
void DELAY_S(unsigned int delaytime);
void SPI_Delay(unsigned char xrate);
void SPI_Write(unsigned char value);
void Epaper_Write_Command(unsigned char command);
void Epaper_Write_Data(unsigned char data);

bool Epaper_WaitBusy(uint32_t timeout_ms);
void Epaper_READBUSY(void);

void EPD_HW_Init(void);
void EPD_Part_Init(void);
void EPD_HW_Init_GUI(void);
void EPD_Update(void);

void EPD_WhiteScreen_White(void);
void EPD_DeepSleep(void);

void EPD_WhiteScreen_ALL(const unsigned char * BWdatas,const unsigned char * RWdatas);
void EPD_Display(unsigned char *BWImage,unsigned char *RWImage);

#endif
