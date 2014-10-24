
const int buttonPin = A0;


// Buttons
const int TIMEBUTTON = 1;
const int P1INC = 2;
const int P1DEC = 3;
const int P2INC = 4;
const int P2DEC = 5;
const int RESETBUTTON = 6;

// Intervals
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
    int buttonState = getButton(analogRead(buttonPin));

    if (buttonState != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        doButtonAction(buttonState);
        lastDebounceTime = millis();
    }
    lastButtonState = buttonState;
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
