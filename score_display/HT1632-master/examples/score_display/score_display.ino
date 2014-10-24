#include "HT1632.h"
#include <stdlib.h>

#define DATA 2
#define WR 3
#define CS1 4
#define CS2 5
#define SOUND_PIN 13

#define SCREEN_WIDTH 48
#define SCREEN_HEIGHT 16

HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS1, CS2);

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  matrix.begin(HT1632_COMMON_16NMOS);
  matrix.setTextSize(2);    // size 1 == 8 pixels high
  matrix.setTextColor(1);   // 'lit' LEDs

  //set_score(1, 1); // kolla om det är tvåsiffrigt
  start_match();
  score_goal(1,0);
  end_match(false);
}

void loop(){}



void start_match() {
  create_explosions(); 
  countdown();
  set_score(0,0);
}

void end_match(boolean playerOneWon) {
  matrix.setBrightness(15);
  matrix.setTextSize(1);
  
  for(int i = SCREEN_WIDTH; i >= 3; --i) {
    //matrix.drawChar(i, 1, 'L', 1, 2);
    if (playerOneWon) {
      matrix.setCursor(i, 1);
      matrix.print("<- 1337");
      matrix.setCursor(i, 9);
      matrix.print("N00B ->");
    } else {
      matrix.setCursor(i, 1);
      matrix.print("1337 ->");
      matrix.setCursor(i, 9);
      matrix.print("<- N00B");
    }
    matrix.writeScreen();
    delay(20);
    if (i > 3)
      matrix.clearScreen();
  }
  
  for (int i = 0; i < 2; ++i) {
    fadeOut();
    fadeIn();
  }
}

void countdown() {
  matrix.setCursor(19, 1); 
  matrix.print(3);
  matrix.writeScreen();
  delay(1000);
  matrix.clearScreen();
  matrix.setCursor(19, 1); 
  matrix.print(2);
  matrix.writeScreen();
  delay(1000);
  matrix.clearScreen();
  matrix.setCursor(19, 1); 
  matrix.print(1);
  matrix.writeScreen();
  delay(1000);
  matrix.clearScreen();
  
  matrix.setTextSize(1);
  matrix.setCursor(1, 5); 
  matrix.print("FUSSBALL!!");
  matrix.writeScreen();
  delay(3000);
  matrix.clearScreen();
  matrix.setTextSize(2);
}


void create_explosions() {
  create_explosion(24, 8, 25, 1);
  create_explosion(13, 7, 4, 0);
  create_explosion(41, 8, 10, 0);
  create_explosion(5, 5, 5, 0);
  create_explosion(15, 7, 20, 0);
}

void create_explosion(int8_t x, int8_t y, int8_t max_radius, uint8_t brightness) {
  for (int8_t r = 0; r <= max_radius; ++r) {
    matrix.fillCircle(x, y, r, brightness);
    matrix.writeScreen();
    delay(50);
  }
}

void set_score(int scoreX, int scoreY) {
  matrix.clearScreen();
  
  matrix.setBrightness(15);
  matrix.setCursor(7, 1);   // start at top left, with one pixel of spacing
  matrix.print(scoreX);
  
  matrix.setCursor(19,1);
  matrix.print("-");
  
  matrix.setCursor(31, 1);   // next line, 8 pixels down
  matrix.print(scoreY);
  matrix.writeScreen();
  
}


void score_goal(int scoreX, int scoreY) {
  
  make_some_noise();
  
  matrix.setBrightness(15);
  
  for(int i = SCREEN_WIDTH; i >= 1; --i) {
    matrix.setCursor(i, 1);
    //matrix.drawChar(i, 1, 'L', 1, 2);
    matrix.print("GOAL");
    matrix.writeScreen();
    delay(20);
    if (i > 1)
      matrix.clearScreen();
  }
  
  for (int i = 0; i < 2; ++i) {
    fadeOut();
    fadeIn();
  }
  fadeOut();
  
  set_score(scoreX, scoreY);
  
  play_tune();
}



void fadeOut() {
  for (int8_t i = 15; i >= 0; --i) {
    matrix.setBrightness(i);
    delay(50);
  }
}

void fadeIn() {
  for (int8_t i = 0; i < 16; ++i) {
    matrix.setBrightness(i);
    delay(50);
  }
}

void play_tune() {
  int numMelodies = 1;

  switch(rand() % numMelodies) {
    case 0: seven_nation_army();
  }
}

void make_some_noise() {
  playNote('G', 125);
  delay(125);
  playNote('G', 125);
  playNote('E', 125);
  playNote('G', 500);
}
	 
  	 
void seven_nation_army() { 	  
  playNote('E', 500);
  delay(250);
  playNote('E', 250);
  playNote('G', 333);
  playNote('E', 333);
  playNote('D', 332);
  playNote('C', 1000);
  playNote('B', 500);
  delay(500);
         
  playNote('E', 500);
  delay(250);
  playNote('E', 250);
  playNote('G', 333);
  playNote('E', 333);
  playNote('D', 332);
  playNote('C', 1000);
  playNote('B', 500);
  delay(500);
}

void playNote(char note, int to_delay) {
  switch(note){
    case 'A': beep(SOUND_PIN,3520,to_delay); break;
    case 'B': beep(SOUND_PIN,1976,to_delay); break;
    case 'C': beep(SOUND_PIN,2093,to_delay); break;
    case 'D': beep(SOUND_PIN,2349,to_delay); break;
    case 'E': beep(SOUND_PIN,2637,to_delay); break;
    case 'F': beep(SOUND_PIN,2793,to_delay); break;
    case 'G': beep(SOUND_PIN,3136,to_delay); break;
  }
}


void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds) { 	  	 
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (int x = 0; x < loopTime; ++x) { 	 
    digitalWrite(speakerPin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(delayAmount);
  } 	 
} 
