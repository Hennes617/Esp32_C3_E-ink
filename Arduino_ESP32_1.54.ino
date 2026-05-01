#include "epd_demo.h"
#include "epd_1inch54.h"
#include "epd_gui.h"
#include "fonts.h"

#include <SPI.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 5
#define LED_COUNT 8

Adafruit_NeoPixel led(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setAllLeds(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < LED_COUNT; i++) {
    led.setPixelColor(i, led.Color(r, g, b));
  }
  led.show();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Boot OK");

  // WS2812 Test
  led.begin();
  led.clear();
  led.show();

  setAllLeds(255, 0, 0);
  delay(400);
  setAllLeds(0, 255, 0);
  delay(400);
  setAllLeds(0, 0, 255);
  delay(400);
  setAllLeds(20, 20, 20);

  // E-Paper Pins
  pinMode(BUSY_Pin, INPUT_PULLUP);
  pinMode(RES_Pin, OUTPUT);
  pinMode(DC_Pin, OUTPUT);
  pinMode(CS_Pin, OUTPUT);
  pinMode(SCK_Pin, OUTPUT);
  pinMode(SDI_Pin, OUTPUT);

  EPD_W21_RST_1;

  Serial.println("Pins ready");
}

void loop() {

  // ===== Frame 1: Chaos Linien =====
  EPD_HW_Init();
  Image_Init(BWimage, EPD_WIDTH, EPD_HEIGHT, 90, WHITE);
  Image_Init(RWimage, EPD_WIDTH, EPD_HEIGHT, 90, WHITE);

  EPD_HW_Init_GUI();
  Gui_Clear(WHITE);

  for(int i=0;i<20;i++){
    Gui_Draw_Line(random(0,200), random(0,200),
                  random(0,200), random(0,200),
                  BLACK, PIXEL_1X1, SOLID);
  }

  for(int i=0;i<10;i++){
    Gui_Draw_Circle(random(20,180), random(20,180),
                    random(5,30), RED, EMPTY, PIXEL_1X1);
  }

  EPD_Display(BWimage, RWimage);
  delay(3000);


  // ===== Frame 2: Grid + Glitches =====
  EPD_HW_Init();
  Gui_Clear(WHITE);

  for(int x=0; x<200; x+=20){
    Gui_Draw_Line(x,0,x,200,BLACK,PIXEL_1X1,SOLID);
  }

  for(int y=0; y<200; y+=20){
    Gui_Draw_Line(0,y,200,y,BLACK,PIXEL_1X1,SOLID);
  }

  for(int i=0;i<15;i++){
    Gui_Draw_Rectangle(random(0,150), random(0,150),
                       random(50,200), random(50,200),
                       RED, EMPTY, PIXEL_1X1);
  }

  EPD_Display(BWimage, RWimage);
  delay(3000);


  // ===== Frame 3: Text Spam =====
  EPD_HW_Init();
  Gui_Clear(WHITE);

  for(int i=0;i<10;i++){
    Gui_Draw_Str(random(0,120), random(0,180),
                 "ESP32", &Font16,
                 WHITE, (i%2==0)?BLACK:RED);
  }

  Gui_Draw_Str(20, 90, "E-PAPER CHAOS", &Font20, WHITE, RED);

  EPD_Display(BWimage, RWimage);
  delay(3000);


  // ===== Frame 4: Invert Chaos =====
  EPD_HW_Init();
  Gui_Clear(WHITE);

  for(int i=0;i<40;i++){
    Gui_Draw_Point(random(0,200), random(0,200),
                   (i%2==0)?BLACK:RED,
                   PIXEL_3X3, DOT_STYLE_DFT);
  }

  for(int i=0;i<10;i++){
    Gui_Draw_Circle(random(20,180), random(20,180),
                    random(10,40),
                    BLACK, FULL, PIXEL_1X1);
  }

  EPD_Display(BWimage, RWimage);
  delay(3000);

}