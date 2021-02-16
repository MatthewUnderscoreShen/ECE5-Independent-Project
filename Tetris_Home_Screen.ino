#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  Serial.begin(9600);
  tft.begin();
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  tft.setRotation(2);
 
  int testText(); {
    tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    tft.setCursor(50,100);
    tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(4);
    tft.println("TETRIS");
    tft.setCursor(75,140);
    tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
    tft.println("The Game");
  }
}

void loop(void) {
  
}
