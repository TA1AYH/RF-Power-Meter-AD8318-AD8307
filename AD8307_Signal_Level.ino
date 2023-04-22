// **** AD8307 or AD8318 ****
// TA1AYH Mehmet Simsek
// Arduino Micro Pro
// 73's
#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);

const int Buzzer_PIN = 10;
const int AD8307_PIN = A0;
// const int AD8318_PIN = A0;


// graph
const int WIDTH = 128;
const int HEIGHT = 64;
const int LENGTH = WIDTH;
float RF_Val = 0;
uint8_t Level = 0;

void setup() {
}

void loop() {
  RF_Val = map(analogRead(AD8307_PIN), 61, 515, 0, 100);  // AD8307
                                                          // RF_Val = map(analogRead(AD8318_PIN), 430, 97, 0, 100);  // AD8318

  if (RF_Val < 0) RF_Val = 0;
  else if (RF_Val > 100) RF_Val = 100;

  if (RF_Val < 1) Level = 0;
  else if (RF_Val < 21) Level = 1;
  else if (RF_Val < 41) Level = 2;
  else if (RF_Val < 61) Level = 3;
  else if (RF_Val < 81) Level = 4;
  else if (RF_Val < 101) Level = 5;

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
    u8g.drawFrame(10, 60, 10, 2);
    u8g.drawFrame(30, 52, 10, 10);
    u8g.drawFrame(50, 42, 10, 20);
    u8g.drawFrame(70, 32, 10, 30);
    u8g.drawFrame(90, 22, 10, 40);
    u8g.drawFrame(110, 12, 10, 50);
  } else if (Level == 1) {
    u8g.drawBox(10, 60, 10, 2);
    u8g.drawBox(30, 52, 10, 10);
    u8g.drawFrame(50, 42, 10, 20);
    u8g.drawFrame(70, 32, 10, 30);
    u8g.drawFrame(90, 22, 10, 40);
    u8g.drawFrame(110, 12, 10, 50);
  } else if (Level == 2) {
    u8g.drawBox(10, 60, 10, 2);
    u8g.drawBox(30, 52, 10, 10);
    u8g.drawBox(50, 42, 10, 20);
    u8g.drawFrame(70, 32, 10, 30);
    u8g.drawFrame(90, 22, 10, 40);
    u8g.drawFrame(110, 12, 10, 50);
  } else if (Level == 3) {
    u8g.drawBox(10, 60, 10, 2);
    u8g.drawBox(30, 52, 10, 10);
    u8g.drawBox(50, 42, 10, 20);
    u8g.drawBox(70, 32, 10, 30);
    u8g.drawFrame(90, 22, 10, 40);
    u8g.drawFrame(110, 12, 10, 50);
  } else if (Level == 4) {
    u8g.drawBox(10, 60, 10, 2);
    u8g.drawBox(30, 52, 10, 10);
    u8g.drawBox(50, 42, 10, 20);
    u8g.drawBox(70, 32, 10, 30);
    u8g.drawBox(90, 22, 10, 40);
    u8g.drawFrame(110, 12, 10, 50);
  } else if (Level == 5) {
    u8g.drawBox(10, 60, 10, 2);
    u8g.drawBox(30, 52, 10, 10);
    u8g.drawBox(50, 42, 10, 20);
    u8g.drawBox(70, 32, 10, 30);
    u8g.drawBox(90, 22, 10, 40);
    u8g.drawBox(110, 12, 10, 50);
  }
}