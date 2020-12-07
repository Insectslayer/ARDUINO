#ifndef ARDUINO_PROJECTS_ROOT_RGB_LED_DRIVER_H
#define ARDUINO_PROJECTS_ROOT_RGB_LED_DRIVER_H

#include <Arduino.h>
#include <Service.h>

struct Color
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct ColorPins
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

class RGBLEDDriver : Service
{
private:
    Color color;
    ColorPins color_pins;

public:
    // Create LED Driver, set up pins and set the color to black.
    // Pins must be PWM-enabled.
    RGBLEDDriver(uint8_t pin_red, uint8_t pin_green, uint8_t pin_blue);

    // Get the current color in RGB.
    Color getColor();

    // Set the current color in RGB.
    void setColor(uint8_t red, uint8_t green, uint8_t blue);

    void cycle() override;

    ~RGBLEDDriver();
};

#endif //ARDUINO_PROJECTS_ROOT_RGB_LED_DRIVER_H