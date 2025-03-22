#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <Adafruit_NeoPixel.h>
#include <Adafruit_LIS3DH.h>
#include <Bounce2.h>
#include <night_light.hpp>

// PIN
#define BTN_PIN 1
#define DC_MOTOR_PIN 2
#define VBR_MOTOR_PIN 3
#define LED_PIN 4
#define NEOPXL_PIN 5
#define ACCEL_INT1_PIN 0
#define PHOTO_PIN A1
#define MSM_CURR_PIN A2

// Neopixel setup
#define NUMPIXELS 1

// main
#define TIMEOUT 400 // Time window (ms) for double press
#define NUM_STATE 4

// State Indicator
#define DOT_LENGTH 100 // ms

// Night Light
#define NCOLORS 4
#define RED 0
#define GREEN 1
#define BLUE 2
#define WHITE 3

#define TIME_ON 10000
#define BRIGHTNESS_THRESHOLD 10
#define ACC_CALIBRATION 1 / 1632.653
#define ACC_DIFF_THRESHOLD 0.6

// Wasserwaage
#define WASSERWAAGE_NMODE 2
#define WASSERWAAGE_INTENSITY_MODE 0
#define WASSERWAAGE_COLOR_MODE 1

// Accelerometer setup
extern Adafruit_LIS3DH lis;

extern Adafruit_NeoPixel pixels;

// Button handling
extern Bounce2::Button button;

void Config();
void RGB_LED_Config();
void Button_Config();
void Accelerometer_Config();

#endif