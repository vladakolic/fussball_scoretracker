const int buttonPin = A0;

const int TIMEBUTTON = 1;
const int P1INC = 2;
const int P1DEC = 3;
const int P2INC = 4;
const int P2DEC = 5;
const int RESETBUTTON = 6;

const int TIMEBUTTONLOW = 80;
const int TIMEBUTTONHIGH = 100;
const int P1INCLOW = 300;
const int P1INCHIGH = 320;
const int P1DECLOW = 370;
const int P1DECHIGH = 390;
const int P2INCLOW = 115;
const int P2INCHIGH = 135;
const int P2DECLOW = 320;
const int P2DECHIGH = 240;
const int RESETBUTTONLOW = 230;
const int RESETBUTTONHIGH = 250;

int buttonState;
int lastButtonState = LOW;
boolean running = false;


long lastDebounceTime = 0;
long debounceDelay = 50;

void setup()
{
    pinMode(buttonPin, INPUT);
    Serial.begin(9600);
}

void loop()
{
    int reading = analogRead(buttonPin);
    int tmpButtonState = LOW;

    if(reading>P2DECLOW && reading<P2DECHIGH)
    {
        tmpButtonState = P2DEC;
    }
    else if(reading>P2INCLOW && reading<P2INCHIGH)
    {
        tmpButtonState = P2INC;
    }
    else if(reading>P1DECLOW && reading<P1DECHIGH)
    {
        tmpButtonState = P1DEC;
    }
    else if(reading>P1INCLOW && reading<P1INCHIGH)
    {
        tmpButtonState = P1INC;
    }
    else if(reading>TIMEBUTTONLOW && reading<TIMEBUTTONHIGH)
    {
        tmpButtonState = TIMEBUTTON;
    }
    else if(reading>RESETBUTTONLOW && reading<RESETBUTTONHIGH)
    {
        tmpButtonState = RESETBUTTON;
    }
    else
    {
        // nothing pressed
        tmpBut tonState = LOW;
    }

    if (tmpButtonState != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        buttonState = tmpButtonState;
    }

    lastButtonState = tmpButtonState;

    switch(buttonState)
    {
        case TIMEBUTTON:
            if (running)
            {
                // stop clock
                Serial.println(TIMEBUTTON);
                Serial.println(running);
                running = false;
            }
            else
            {
                // start clock
                Serial.println(TIMEBUTTON);
                Serial.println(running);
                running = true;
            }
            break;
        case P1INC:
            // inc p1 score
            Serial.println(P1INC);
            break;
        case P1DEC:
            // dec p1 score
            Serial.println(P1DEC);
            break;
        case P2INC:
            // inc p2 score
            Serial.println(P2INC);
            break;
        case P2DEC:
            // dec p2 score
            Serial.println(P2DEC);
            break;
        case RESETBUTTON:
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
