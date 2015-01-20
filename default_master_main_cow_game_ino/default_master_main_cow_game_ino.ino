#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include "score_display.h"
#include "HT1632.h"

Adafruit_7segment gameClock = Adafruit_7segment();

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

//IR sensor stuff
// Vad gör dom här två?
//int dtect=8;
//int buzzpin=9;

int goalOneSensor=A1;
int goalTwoSensor=A2;
int goalOneThreshold = 900;
int goalTwoThreshold = 900;



void setup()
{
    Serial.begin(9600);
    Serial.println("Setup");
    pinMode(buttonPin, INPUT);
    pinMode(goalOneSensor,INPUT);
    pinMode(goalTwoSensor,INPUT);
    gameClock.begin(0x70);

    // try to print a number thats too long
    gameClock.print(10000, DEC);
    gameClock.writeDisplay();
    delay(500);

    gamestart = millis();
    Serial.println("Yoo, let do this");
    startGame();
}

void displayTime() {
    gameClock.println(minutes);
    gameClock.writeDisplay();

    if(minutes % 100 == 0){
        minutes -= 40;
    }
}

void startGame() {
    minutes = 300;
    gamestart = millis();
    start_match();
}

void endGame() {
    for(int16_t inf = 0; inf <= 20; inf++) {
        if(inf % 2 == 0){
            gameClock.print(10000, DEC);
            gameClock.writeDisplay();
            delay(500);
        }
        if(inf % 2 == 1){
            gameClock.println(8888);
            gameClock.writeDisplay();
            delay(500);
        }
    }
}


void loop() {

    int read = analogRead(buttonPin);
    int reading = getButton(read);
    int playerOneSensor=analogRead(goalOneSensor);
    int playerTwoSensor=analogRead(goalTwoSensor);


    if (minutes <= 0) {
        endGame();
    }

    if (millis() - gamestart >= 1000) {
        Serial.println("========");
        //Serial.println(millis());
        //Serial.println(gamestart);
        //Serial.println(millis() - gamestart >= 1000);
        //Serial.println(minutes);
        
        gamestart = millis();
        displayTime();
        minutes--;
    }

    // Serial.println("SensorOne: ");
    // Serial.println(playerOneSensor);
    // Serial.println("SensorTwo: ");
    // Serial.println(playerTwoSensor);

    if (playerOneSensor >= goalOneThreshold) {
       score_goal(++p1score, p2score);
    }

    if (playerTwoSensor >= goalTwoThreshold) {
       score_goal(p1score, ++p2score);
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
            set_score(p1score, p2score);
            break;
        case P1DEC:
            if (p1score > 0)
            {
                p1score--;
            }
            set_score(p1score, p2score);
            break;
        case P2INC:
            p2score++;
            set_score(p1score, p2score);
            break;
        case P2DEC:
            if (p2score > 0)
            {
                p2score--;
            }
            set_score(p1score, p2score);
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

