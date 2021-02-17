#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);
}

void loop() {
  for (int i=0; i<=14; i++) {
    tft.fillRect(100,i*20,20,20,ILI9341_WHITE);
    tft.fillRect(100,(i*20+20),20,20,ILI9341_WHITE);
    tft.fillRect(120,i*20,20,20,ILI9341_WHITE);
    tft.fillRect(80,i*20,20,20,ILI9341_WHITE);
    delay(400);
    tft.fillRect(100,i*20,20,20,ILI9341_BLACK);
    tft.fillRect(100,(i*20+20),20,20,ILI9341_BLACK);
    tft.fillRect(120,i*20,20,20,ILI9341_BLACK);
    tft.fillRect(80,i*20,20,20,ILI9341_BLACK);
    delay(10);
  }

}
