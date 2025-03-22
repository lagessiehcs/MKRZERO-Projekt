#include <night_light.hpp>

// Color
static char color = RED;

static Acceleration acceleration = {0, 0, 0, 0, 0, 0};

// Time
static int start = -TIME_ON;

// Function Prototype
static bool detectMotion();
static void startRGB(char color);
static void stopRGB();
static int readPhotodiode();
static void changeRGB();

void NightLight_Init()
{
    RGB_LED_Config();
    Accelerometer_Config();
    Button_Config();
}

void NightLight_Run()
{
    bool motion = detectMotion();

    int brightness = readPhotodiode();

    if (brightness < BRIGHTNESS_THRESHOLD && motion)
    {
        start = millis();
        changeRGB();
    }
    else if (millis() - start < TIME_ON)
    {
        changeRGB();
    }
    else
    {
        stopRGB();
    }
}

void NightLight_Reset()
{
    // Color
    color = RED;

    acceleration = {0, 0, 0, 0, 0, 0};

    // Time
    start = -TIME_ON;

    stopRGB();
}

static void startRGB(char color)
{
    if (color == RED)
    {
        pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    }
    else if (color == GREEN)
    {
        pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    }
    else if (color == BLUE)
    {
        pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    }
    else if (color == WHITE)
    {
        pixels.setPixelColor(0, pixels.Color(255, 255, 255));
    }
    pixels.show();
}

static void stopRGB()
{
    pixels.clear();
    pixels.show();
}

static int readPhotodiode()
{
    int value = analogRead(PHOTO_PIN);
    return value;
}

static bool detectMotion()
{
    lis.read();

    acceleration.x_old = acceleration.x;
    acceleration.y_old = acceleration.y;
    acceleration.z_old = acceleration.z;

    acceleration.x = lis.x * ACC_CALIBRATION;
    acceleration.y = lis.y * ACC_CALIBRATION;
    acceleration.z = lis.z * ACC_CALIBRATION;

    if (abs(acceleration.x - acceleration.x_old) < ACC_DIFF_THRESHOLD && abs(acceleration.y - acceleration.y_old) < ACC_DIFF_THRESHOLD && abs(acceleration.z - acceleration.z_old) < ACC_DIFF_THRESHOLD)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

static void changeRGB()
{
    button.update();

    if (button.pressed())
    {

        color = (color + 1) % NCOLORS;
    }
    startRGB(color);
}