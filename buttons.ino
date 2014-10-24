// Pins
const int buttonPin = 0;

// Buttons
const int TIMEBUTTON = 1;
const int P1INC = 2;
const int P1DEC = 3;
const int P2INC = 4;
const int P2DEC = 5;
const int RESETBUTTON = 6;

// Intervals
const int TIMEBUTTONLOW = 970;
const int TIMEBUTTONHIGH = 1024;
const int P1INCLOW = 850;
const int P1INCHIGH = 950;
const int P1DECLOW = 700;
const int P1DECHIGH = 800;
const int P2INCLOW = 400;
const int P2INCHIGH = 650;
const int P2DECLOW = 250;
const int P2DECHIGH = 350;
const int RESETBUTTONLOW = 350;
const int RESETBUTTONHIGH = 350;

int lastButtonState = LOW;
boolean running = false;

long lastDebounceTime = 0;
long debounceDelay = 50;

void setup()
{
    pinMode(buttonPin, INPUT);
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
        Delay(100);
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
                running = false;
            }
            else
            {
                // start clock
                running = true;
            }
            break;
        case P1INC:
            // inc p1 score
            break;
        case P1DEC:
            // dec p1 score
            break;
        case P2INC:
            // inc p2 score
            break;
        case P2DEC:
            // dec p2 score
            break;
        case RESETBUTTON:
            // reset time and scores
            running = false;
            break;
        default:
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
