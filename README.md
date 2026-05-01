# ESP32-C3 1.54" Tri-Color E-Paper (200x200)

Arduino-compatible driver and drawing utilities for a 1.54" tri-color e-paper display (black/white/red) on an ESP32-C3 SuperMini.

This repository contains the display driver, drawing primitives, fonts, and demo image data.  
It currently does **not** include a `.ino` sketch file, so you add your own sketch entrypoint.

## Features

- 200x200 tri-color panel support (black + red layers)
- Full-frame refresh pipeline
- Software SPI-style signaling via GPIO
- Drawing API: pixels, lines, rectangles, circles, text
- Built-in ASCII fonts: 8, 12, 16, 20, 24 px
- Example bitmap data in `epd_demo.h`

## Hardware

- ESP32-C3 SuperMini (3.3V logic)
- 1.54" tri-color e-paper display module (200x200)
- Stable 3.3V power source

### Wiring (from the current code defaults)

| ESP32-C3 SuperMini | E-Paper Pin |
|---|---|
| 3V3 | VCC |
| GND | GND |
| GPIO7 | CS |
| GPIO4 | CLK |
| GPIO6 | MOSI (DIN) |
| GPIO2 | DC |
| GPIO3 | RST |
| GPIO1 | BUSY |

Optional onboard LED test (if present on your board):

- `GPIO5` -> WS2812B data

## Repository Layout

- `epd_1inch54.h/.cpp`: low-level panel driver and refresh commands
- `epd_gui.h/.cpp`: drawing primitives + frame-buffer logic
- `fonts.h` + `font*.cpp`: built-in font tables
- `epd_demo.h`: large bitmap demo array

## Quick Start (Arduino IDE)

1. Install **Arduino IDE 2.x**.
2. Install **ESP32 by Espressif Systems** in Boards Manager.
3. Select your board (usually `ESP32C3 Dev Module` or your SuperMini variant).
4. Put all files from this repo into one Arduino sketch folder.
5. Create a sketch file (for example `Arduino_ESP32_1.54.ino`) next to these files.
6. Upload the example below.

## Minimal Example Sketch

```cpp
#include "epd_1inch54.h"
#include "epd_gui.h"
#include "fonts.h"

void setup() {
  Serial.begin(115200);
  delay(300);

  // Pin modes from epd_1inch54.h
  pinMode(BUSY_Pin, INPUT_PULLUP);
  pinMode(RES_Pin, OUTPUT);
  pinMode(DC_Pin, OUTPUT);
  pinMode(CS_Pin, OUTPUT);
  pinMode(SCK_Pin, OUTPUT);
  pinMode(SDI_Pin, OUTPUT);

  // Init display + frame buffers
  EPD_HW_Init();
  Image_Init(BWimage, EPD_WIDTH, EPD_HEIGHT, ROTATE_0, WHITE);
  Image_Init(RWimage, EPD_WIDTH, EPD_HEIGHT, ROTATE_0, WHITE);
  EPD_HW_Init_GUI();

  // Draw content
  Gui_Clear(WHITE);
  Gui_Draw_Str(12, 20, "ESP32-C3 E-Paper", &Font16, WHITE, BLACK);
  Gui_Draw_Rectangle(10, 55, 190, 120, RED, EMPTY, PIXEL_1X1);
  Gui_Draw_Circle(100, 160, 28, BLACK, EMPTY, PIXEL_1X1);

  // Push frame to display
  EPD_Display(BWimage, RWimage);
  EPD_DeepSleep();
}

void loop() {
  // E-paper is static; nothing needed here.
}
```

## Typical Drawing Flow

1. Configure GPIO pin modes.
2. Call `EPD_HW_Init()`.
3. Initialize both buffers with `Image_Init(BWimage, ...)` and `Image_Init(RWimage, ...)`.
4. Call `EPD_HW_Init_GUI()`.
5. Clear/draw using `Gui_*` functions.
6. Call `EPD_Display(BWimage, RWimage)`.
7. Optionally call `EPD_DeepSleep()` to reduce power.

## Notes and Limits

- Display size is fixed at `200x200`.
- Each layer buffer is `5000` bytes (`200 * 200 / 8`).
- This code path is full-refresh oriented (not partial-refresh optimized).
- `BUSY` is polled in a blocking loop; wiring/power issues can make updates hang.

## Troubleshooting

- Stuck update: verify `BUSY` wiring and panel power.
- No image or noise: recheck pin mapping (`CS/CLK/MOSI/DC/RST/BUSY`) and common ground.
- Wrong orientation: change `ROTATE_0/90/180/270` in `Image_Init(...)`.
- Compile errors about missing symbols: ensure all `.cpp/.h` files are in the same sketch folder.

## License

This project is licensed under the MIT License.  
See the `LICENSE` file for details.
