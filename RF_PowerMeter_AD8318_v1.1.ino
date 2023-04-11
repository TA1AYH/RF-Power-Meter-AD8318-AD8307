//AD8318 v1.1
//**for Arduino Micro Pro**
// 73's
#include "U8glib.h"
U8GLIB_SH1106_128X64_2X u8g(U8G_I2C_OPT_NO_ACK);
#if defined(ESP8266) || defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif
const int eepromWindowAdress = 4;
const int Buzzer_PIN = 10;
const int AD8318_PIN = A0;  //A0
int eepromWindow = 0;

// arc
int xmax = 131;
int ymax = 64;
int xcenter = xmax / 2;
int ycenter = ymax / 2 + 10;
int arc = ymax / 2;
int maxf = 10;
uint8_t Angle = 0;
volatile int blink = 0;
unsigned long blinkTime = 0;

// graph
const int WIDTH = 128;
const int HEIGHT = 64;
const int LENGTH = WIDTH;
int x = 19;
int y[LENGTH];
int DisplayType = 0;
float RF_Val = 0;
int Cleared = 0;
unsigned long Max_Time = 0;
float Max_Val = 0;
String Max_ValT;

void setup() {
  pinMode(Buzzer_PIN, OUTPUT);
  //Serial.begin(115200);
  eepromWindow = readIntFromEEPROM(eepromWindowAdress);
  if (eepromWindow == 0) {
    eepromWindow = 1;
  } else {
    eepromWindow = 0;
  }
  SavetoEEPROM(eepromWindowAdress, eepromWindow);
}

void loop() {
  RF_Val = map(analogRead(AD8318_PIN), 430, 97, 0, 75);

  if (RF_Val < 0) RF_Val = 0;
  else if (RF_Val > 75) RF_Val = 75;

  if (RF_Val > Max_Val) {
    Max_Val = RF_Val;
    Max_Time = millis();
    maxf = 1; /*
    if (eepromWindow == 0) {
      digitalWrite(Buzzer_PIN, HIGH);
      delay(50);
      digitalWrite(Buzzer_PIN, LOW);
      delay(50);*/

  } else if ((millis() - Max_Time) > 10000) {
    Max_Val = RF_Val;
    Max_Time = millis();
    maxf = 0;
  }
  Max_ValT = String(Max_Val - 70, 0);

  if ((millis() - blinkTime) > 500) {
    if (blink == 0) blink = 1;
    else blink = 0;
    blinkTime = millis();
  }

  if (eepromWindow == 0) {
    Graph();
    delay(50);
  } else {
    if (RF_Val >= 70) {
      digitalWrite(Buzzer_PIN, HIGH);
    } else if (RF_Val > 37) {
      //digitalWrite(Buzzer_PIN, LOW);
      digitalWrite(Buzzer_PIN, HIGH);
      delay(370 - (RF_Val - 5) * 5);
      digitalWrite(Buzzer_PIN, LOW);
      delay(370 - (RF_Val - 5) * 5);
    } else if (RF_Val < 70) {
      digitalWrite(Buzzer_PIN, LOW);
    }
    Arcer();
  }
}
void Arcer() {
  Angle = map(RF_Val, 0, 75, 0, 90);

  if (Angle < 45) {
    Angle = Angle + 135;
  } else {
    Angle = Angle - 45;
  }

  u8g.firstPage();
  do {
    gauge(Angle);
  } while (u8g.nextPage());
}
// ------------------------------------------------- void gauge() ------------------------------------------

void gauge(uint8_t angle) {
  u8g.drawCircle(xcenter, ycenter, arc + 6, U8G_DRAW_UPPER_RIGHT);
  u8g.drawCircle(xcenter, ycenter, arc + 4, U8G_DRAW_UPPER_RIGHT);
  u8g.drawCircle(xcenter, ycenter, arc + 6, U8G_DRAW_UPPER_LEFT);
  u8g.drawCircle(xcenter, ycenter, arc + 4, U8G_DRAW_UPPER_LEFT);

  float x1 = sin(2 * angle * 2 * 3.14 / 360);
  float y1 = cos(2 * angle * 2 * 3.14 / 360);

  u8g.drawLine(xcenter, ycenter, xcenter + arc * x1, ycenter - arc * y1);
  u8g.drawLine(xcenter, ycenter, xcenter + arc * sin(2 * 38.5 * 2 * 3.14 / 360), ycenter - arc * cos(2 * 38.5 * 2 * 3.14 / 360));

  u8g.drawDisc(xcenter, ycenter, 5, U8G_DRAW_UPPER_LEFT);
  u8g.drawDisc(xcenter, ycenter, 5, U8G_DRAW_UPPER_RIGHT);

  u8g.setFont(u8g_font_chikita);
  u8g.setFont(u8g_font_6x10);


  u8g.setPrintPos(56, 29);
  if (blink == 0)
    u8g.print("dBm");
  else
    u8g.print("   ");

  u8g.setPrintPos(2, 60);
  u8g.print("TA1AYH");



  u8g.drawStr(6, 42, "-70");
  u8g.drawStr(16, 18, "-51");
  u8g.drawStr(54, 16, "-32");
  u8g.drawStr(97, 18, "-14");
  u8g.drawStr(110, 42, "5");

  int DBM_Val = map(RF_Val, 0, 75, -70, 5);

  u8g.setFont(u8g_font_profont22);
  if (DBM_Val >= 0) {
    u8g.setPrintPos(57, 62);
  } else {
    u8g.setPrintPos(47, 62);
  }
  u8g.print(DBM_Val);
  if (maxf == 0) u8g.setFont(u8g_font_6x10);
  else u8g.setFont(u8g_font_helvR14r);
  u8g.setPrintPos(95, 62);
  u8g.print(Max_ValT.c_str());
}
// ------------------------------------------------- void Graph()  ------------------------------------------
void Graph() {
  if (Cleared == 0) {
    x = 19;
    clearY();
    Cleared = 1;
  }

  y[x] = map(RF_Val, 0, 75, HEIGHT - 4, 13);

  u8g.firstPage();
  do {
    drawChart();
    drawY();
    u8g.drawStr(0, y[x] + 2, String(RF_Val - 70, 0).c_str());  //
    //u8g.drawRFrame(0, 0, 94, 13, 2);  // draws frame with rounded edges
    u8g.setFont(u8g_font_6x10);
    u8g.setPrintPos(2, 10);
    u8g.print("TA1AYH");

    u8g.setPrintPos(55, 10);
    u8g.print("Max");
    if (maxf == 1) {
      u8g.setPrintPos(80, 13);
      u8g.setFont(u8g_font_helvR14r);
    } else {
      u8g.setPrintPos(80, 10);
    }
    u8g.print(Max_ValT.c_str());
      u8g.setFont(u8g_font_6x10);
    u8g.setPrintPos(110, 10);
    u8g.print("dBm");

  } while (u8g.nextPage());

  x++;
  if (x >= WIDTH - 1) {
    Cleared = 0;
  } else if (y[x] >= HEIGHT - 13) {
    Cleared = 0;
  }
}
void drawChart() {
  u8g.drawLine(19, 14, 19, 63);  // Y ax
  //  u8g.drawLine(19, 20, 128, 20);  // X ax

  for (int i = 14; i <= WIDTH; i = i + 10) {
    if (i <= LENGTH) {
      if (i > 20) {
        //u8g.drawPixel(i, 19);
        u8g.drawPixel(i, 20);
      }
      u8g.drawPixel(20, i);
      u8g.drawPixel(21, i);
    } else if (i <= WIDTH) {
      //u8g.drawPixel(i, 19);
      u8g.drawPixel(i, 20);
    }
  }
}
void drawY() {
  for (int i = 20; i < LENGTH; i++) {
    if (y[i] != -1) {
      //u8g.drawPixel(i - 1, y[i - 1]);
      u8g.drawLine(i - 1, y[i - 1], i, y[i]);
    } else {
      break;
    }
  }
}

void clearY() {
  for (int i = 0; i < LENGTH; i++) {
    y[i] = -1;
  }
}


void SavetoEEPROM(int address, int number) {
  byte byte1 = number >> 8;
  byte byte2 = number & 0xFF;
  EEPROM.write(address, byte1);
  EEPROM.write(address + 1, byte2);
}
int readIntFromEEPROM(int address) {
  return (EEPROM.read(address) << 8) + EEPROM.read(address + 1);
}