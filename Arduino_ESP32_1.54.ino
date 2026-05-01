#include "epd_1inch54.h"
#include "epd_gui.h"
#include "fonts.h"

static const unsigned long REFRESH_INTERVAL_MS = 180000UL; // Recommended minimum for tri-color panels

static unsigned long last_refresh_ms = 0;
static uint32_t frame_id = 0;

static void setup_epd_pins()
{
  pinMode(BUSY_Pin, INPUT_PULLUP);
  pinMode(RES_Pin, OUTPUT);
  pinMode(DC_Pin, OUTPUT);
  pinMode(CS_Pin, OUTPUT);
  pinMode(SCK_Pin, OUTPUT);
  pinMode(SDI_Pin, OUTPUT);
}

static void init_display()
{
  EPD_HW_Init();
  Image_Init(BWimage, EPD_WIDTH, EPD_HEIGHT, ROTATE_0, WHITE);
  Image_Init(RWimage, EPD_WIDTH, EPD_HEIGHT, ROTATE_0, WHITE);
  EPD_HW_Init_GUI();
}

static void draw_frame(uint32_t id)
{
  Gui_Clear(WHITE);

  Gui_Draw_Str(10, 10, "ESP32-C3 E-Paper Test", &Font12, WHITE, BLACK);
  Gui_Draw_Str(10, 30, "Tri-color full refresh", &Font12, WHITE, RED);

  Gui_Draw_Str(10, 52, "Frame:", &Font12, WHITE, BLACK);
  Gui_Draw_Num(70, 52, (int32_t)id, &Font12, WHITE, BLACK);

  // Simple visual marker that changes every frame.
  uint16_t x = 20 + (id % 8) * 20;
  Gui_Draw_Rectangle(10, 80, 190, 160, BLACK, EMPTY, PIXEL_1X1);
  Gui_Draw_Circle(x, 120, 12, RED, FULL, PIXEL_1X1);
}

static void refresh_display()
{
  unsigned long t0 = millis();

  draw_frame(frame_id);
  EPD_Display(BWimage, RWimage);

  unsigned long dt = millis() - t0;
  Serial.print("Frame ");
  Serial.print(frame_id);
  Serial.print(" done in ");
  Serial.print(dt);
  Serial.println(" ms");

  frame_id++;
  last_refresh_ms = millis();
}

void setup()
{
  Serial.begin(115200);
  delay(300);
  Serial.println("EPD test start");

  setup_epd_pins();
  init_display();
  refresh_display();
}

void loop()
{
  if ((millis() - last_refresh_ms) >= REFRESH_INTERVAL_MS)
  {
    refresh_display();
  }
}

