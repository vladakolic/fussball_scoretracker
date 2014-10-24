#include "HT1632-master/HT1632.h"

#define DATA 2
#define WR 3
#define CS1 4
#define CS2 5

HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS1, CS2);

void setup() {
  Serial.begin(9600);
  matrix.begin(HT1632_COMMON_16NMOS);
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();
}

void loop() {
  matrix.blink(true);
  delay(2000);
  matrix.blink(false);
  delay(2000);
}
