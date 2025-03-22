#include <config.hpp>

// Accelerometer setup
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPXL_PIN, NEO_GRB + NEO_KHZ800);

// Button handling
Bounce2::Button button = Bounce2::Button();

void Config()
{
    pinMode(LED_PIN, OUTPUT);
    RGB_LED_Config();
    Button_Config();
    Accelerometer_Config();
}

void RGB_LED_Config()
{
    // Initialize Neopixel
    pixels.begin();
}

void Button_Config()
{
    // Pin setups
    pinMode(BTN_PIN, INPUT_PULLUP);
    // Initialize button debouncer
    button.attach(BTN_PIN);
    button.interval(10); // 10ms debounce interval
    button.setPressedState(LOW);
    delay(3000);
}

void Accelerometer_Config()
{
    if (!lis.begin(0x19))
    {
        Serial.println("Could not find LIS3DH accelerometer!");
        while (1)
            ;
    }
    lis.setRange(LIS3DH_RANGE_2_G);
    lis.setDataRate(LIS3DH_DATARATE_50_HZ);
    pinMode(ACCEL_INT1_PIN, INPUT_PULLUP);
}