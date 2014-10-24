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

void setup()
{
    pinMode(buttonPin, INPUT);
    Serial.begin(9600);
}

void loop()
{

    int read = analogRead(buttonPin);
    int reading = getButton(read);

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
