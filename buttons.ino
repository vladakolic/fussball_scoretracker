const int buttonPin = 0;

const int TIMEBUTTON = 1;
const int P1INC = 2;
const int P1DEC = 3;
const int P2INC = 4;
const int P2DEC = 5;
const int RESETBUTTON = 6;

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

int buttonState;
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
