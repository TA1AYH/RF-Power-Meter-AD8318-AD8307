// **** AD8307 or AD8318 ****
// TA1AYH Mehmet Simsek
// Arduino Micro Pro
// 73's
#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);

const int Buzzer_PIN = 10;
const int AD8307_PIN = A0;
const int AD8318_PIN = A0;


// graph
const int WIDTH = 128;
const int HEIGHT = 64;
const int LENGTH = WIDTH;
float RF_Val = 0;
uint8_t Level = 0;

void setup() {
}

void loop() {
  RF_Val = map(analogRead(AD8307_PIN), 61, 515, 0, 60);  // AD8307
  //RF_Val = map(analogRead(AD8318_PIN), 430, 97, 0, 60);  // AD8318

  if (RF_Val < 0) RF_Val = 0;
  else if (RF_Val > 60) RF_Val = 60;

  if (RF_Val < 2) Level = 0;
  else if (RF_Val < 13) Level = 1;
  else if (RF_Val < 25) Level = 2;
  else if (RF_Val < 37) Level = 3;
  else if (RF_Val < 49) Level = 4;
  else if (RF_Val < 61) Level = 5;

  Graph();
  delay(100);
}
// ------------------------------------------------- void Graph()  ------------------------------------------
void Graph() {
  u8g.firstPage();
  do {
    drawLevels();
  } while (u8g.nextPage());
}

void drawLevels() {
  if (Level == 0) {
    u8g.drawFrame(10, 58, 10, 2);
    u8g.drawFrame(30, 48, 10, 12);
    u8g.drawFrame(50, 36, 10, 24);
    u8g.drawFrame(70, 24, 10, 36);
    u8g.drawFrame(90, 12, 10, 48);
    u8g.drawFrame(110, 0, 10, 60);
  } else if (Level == 1) {
    u8g.drawBox(10, 58, 10, 2);
    u8g.drawFrame(30, 48, 10, 12);
    u8g.drawBox(30, 48 + (12 - RF_Val), 10, RF_Val);
    u8g.drawFrame(50, 36, 10, 24);
    u8g.drawFrame(70, 24, 10, 36);
    u8g.drawFrame(90, 12, 10, 48);
    u8g.drawFrame(110, 0, 10, 60);
  } else if (Level == 2) {
    u8g.drawBox(10, 58, 10, 2);
    u8g.drawBox(30, 48, 10, 12);
    u8g.drawFrame(50, 36, 10, 24);
    u8g.drawBox(50, 36 + (24 - RF_Val), 10, RF_Val);
    u8g.drawFrame(70, 24, 10, 36);
    u8g.drawFrame(90, 12, 10, 48);
    u8g.drawFrame(110, 0, 10, 60);
  } else if (Level == 3) {
    u8g.drawBox(10, 58, 10, 2);
    u8g.drawBox(30, 48, 10, 12);
    u8g.drawBox(50, 36, 10, 24);
    u8g.drawFrame(70, 24, 10, 36);
    u8g.drawBox(70, 24 + (36 - RF_Val), 10, RF_Val);
    u8g.drawFrame(90, 12, 10, 48);
    u8g.drawFrame(110, 0, 10, 60);
  } else if (Level == 4) {
    u8g.drawBox(10, 58, 10, 2);
    u8g.drawBox(30, 48, 10, 12);
    u8g.drawBox(50, 36, 10, 24);
    u8g.drawBox(70, 24, 10, 36);
    u8g.drawFrame(90, 12, 10, 48);
    u8g.drawBox(90, 12 + (48 - RF_Val), 10, RF_Val);
    u8g.drawFrame(110, 0, 10, 60);
  } else if (Level == 5) {
    u8g.drawBox(10, 58, 10, 2);
    u8g.drawBox(30, 48, 10, 12);
    u8g.drawBox(50, 36, 10, 24);
    u8g.drawBox(70, 24, 10, 36);
    u8g.drawBox(90, 12, 10, 48);
    u8g.drawFrame(110, 0, 10, 60);
    u8g.drawBox(110, 0 + (60 - RF_Val), 10, RF_Val);
  }
}