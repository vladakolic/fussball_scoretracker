#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();

const int buttonPin = A0;
  
// Buttons
const int TIMEBUTTON = 1;
const int P1INC = 2;
const int P1DEC = 3;
const int P2INC = 4;
const int P2DEC = 5;
const int RESETBUTTON = 6;

// Intervals
const int TIMEBUTTONLOW = 933;
const int TIMEBUTTONHIGH = 953;
const int P1INCLOW = 350;
const int P1INCHIGH = 370;
const int P1DECLOW = 423;
const int P1DECHIGH = 443;
const int P2INCLOW = 142;
const int P2INCHIGH = 162;
const int P2DECLOW = 262;
const int P2DECHIGH = 282;
const int RESETBUTTONLOW = 860;
const int RESETBUTTONHIGH = 880;

// Button state variables
int buttonState;
int lastButtonState = LOW;

// Debouncing
long lastDebounceTime = 0;
long debounceDelay = 50;

// Game specific constanst
const long GAMETIME = 300000;
const long currentGameTime = GAMETIME;

// Game specific variables
int p1score = 0;
int p2score = 0;
boolean running = false;

// Game start
unsigned long gamestart = 0;
int minutes = 300;





void setup()
{
    Serial.begin(9600);
    Serial.println("Setup");
    pinMode(buttonPin, INPUT);
    matrix.begin(0x70);

    // try to print a number thats too long
    matrix.print(10000, DEC);
    matrix.writeDisplay();
    delay(500);

    gamestart = millis();
    Serial.println("Yoo, let do this");
}

void displayTime() {
    matrix.println(minutes);
    matrix.writeDisplay();

    if(minutes % 100 == 0){
        minutes -= 40;
    }
}

void startGame() {
    minutes = 300;
    gamestart = millis();
}

void endGame() {
    for(int16_t inf = 0; inf <= 20; inf++) {
        if(inf % 2 == 0){
            matrix.print(10000, DEC);
            matrix.writeDisplay();
            delay(500);
        }
        if(inf % 2 == 1){
            matrix.println(8888);
            matrix.writeDisplay();
            delay(500);
        }
    }
}


void loop() {

    int read = analogRead(buttonPin);
    int reading = getButton(read);

    if (minutes <= 0) {
        endGame();
    }

    if (millis() - gamestart >= 1000) {
        Serial.println("========");
        Serial.println(millis());
        Serial.println(gamestart);
        Serial.println(millis() - gamestart >= 1000);
        Serial.println(minutes);
        
        gamestart = millis();
        displayTime();
        minutes--;
    }

    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (reading != buttonState)
        {
            buttonState = reading;
            doButtonAction(buttonState);
        }
    }

    lastButtonState = reading;
}


void doButtonAction(int buttonState)
{
    switch(buttonState)
    {
        case TIMEBUTTON:
            if (running)
            {
                // stop clock
                Serial.println(TIMEBUTTON);
                running = false;
            }
            else
            {
                // start clock
                Serial.println(TIMEBUTTON);
                running = true;
            }
            break;
        case P1INC:
            p1score++;
            break;
        case P1DEC:
            if (p1score > 0)
            {
                p1score--;
            }
            break;
        case P2INC:
            p1score++;
            break;
        case P2DEC:
            if (p2score > 0)
            {
                p2score--;
            }
            break;
        case RESETBUTTON:
            endGame();
            startGame();

            // reset time and scores
            Serial.println(RESETBUTTON);
            running = false;
            break;
        default:
            Serial.println("doing nothing");
            // do nothing
            break;
    }
}

int getButton(int reading)
{
    if(reading>P2DECLOW && reading<P2DECHIGH)
    {
        return P2DEC;
    }
    else if(reading>P2INCLOW && reading<P2INCHIGH)
    {
        return P2INC;
    }
    else if(reading>P1DECLOW && reading<P1DECHIGH)
    {
        return P1DEC;
    }
    else if(reading>P1INCLOW && reading<P1INCHIGH)
    {
        return P1INC;
    }
    else if(reading>TIMEBUTTONLOW && reading<TIMEBUTTONHIGH)
    {
        return TIMEBUTTON;
    }
    else if(reading>RESETBUTTONLOW && reading<RESETBUTTONHIGH)
    {
        return RESETBUTTON;
    }
    else
    {
        // nothing pressed
        return LOW;
    }
}

