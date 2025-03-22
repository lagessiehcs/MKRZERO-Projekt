#include <state_indicator.hpp>

const char *MORSE[] = {"-----", ".----", "..---", "...--", "....-",
                       ".....", "-....", "--...", "---..", "----."};

volatile unsigned long long msTicks = 0; // Variable to store millisecond ticks
static volatile unsigned long long start = 0;

volatile char morseCode[200]; // Variable to store morse code string

bool onboardLEDState = true;

// Function Prototype
static void StringToMorse(char str[]);
static void sendDot(void);
static void sendDash(void);
static void sendCharacterSpace(void);
static void sendLetterSpace(void);
static void sendWordSpace(void);
static void blinkLED(char morse[]);

void State_Indicator_Init()
{
    pinMode(LED_PIN, OUTPUT);
}

void State_Indicator_Run(int state_number)
{
    char str[20]; // Buffer to store the string
    sprintf(str, "%d", state_number);
    StringToMorse(str);
    blinkLED((char *)morseCode);
}

static void StringToMorse(char str[])
{
    strcpy((char *)morseCode, ""); // Reset morseCode

    int strlength = strlen(str);

    for (int i = 0; i < strlength; i++)
    {
        if (str[i] == ' ')
        {
            // Add two spaces to indicate word space
            strcat((char *)morseCode, "  ");
            continue;
        }
        char upperChar = toupper(str[i]);
        strcat((char *)morseCode, MORSE[upperChar - '0']);
        // If next character is a space, dont add space into morse string
        if (str[i + 1] == ' ')
        {
            continue;
        }
        // And only add one space if it is not the last letter
        if (i < strlength)
        {
            strcat((char *)morseCode, " ");
        }
    }
}

static void sendDot(void)
{
    digitalWrite(LED_PIN, onboardLEDState);
    start = msTicks;
    delay(DOT_LENGTH);
}

static void sendDash(void)
{
    digitalWrite(LED_PIN, onboardLEDState);
    start = msTicks;
    delay(3 * DOT_LENGTH);
}

static void sendCharacterSpace(void)
{
    digitalWrite(LED_PIN, !onboardLEDState);
    start = msTicks;
    delay(DOT_LENGTH);
}

static void sendLetterSpace(void)
{
    digitalWrite(LED_PIN, !onboardLEDState);
    start = msTicks;
    delay(3 * DOT_LENGTH);
}

static void sendWordSpace(void)
{
    digitalWrite(LED_PIN, !onboardLEDState);
    start = msTicks;
    delay(7 * DOT_LENGTH);
}

static void blinkLED(char morse[])
{
    int morseCodeLength = strlen(morse);

    for (int i = 0; i < morseCodeLength; i++)
    {
        if (morse[i] == '.')
        {
            sendDot();
        }
        else if (morse[i] == '-')
        {
            sendDash();
        }
        else if (morse[i] == ' ')
        {
            if (morse[i + 1] == ' ') // Detect word space
            {
                sendWordSpace();
                i++; // Skip the next space
            }
            else
            {
                sendLetterSpace();
            }
        }

        // Detect character space
        if (i < morseCodeLength - 1 && morse[i] != ' ' && morse[i + 1] != ' ')
        {
            sendCharacterSpace();
        }
    }
}