#include <RGBLEDDriver.h>

RGBLEDDriver::RGBLEDDriver(uint8_t pin_red, uint8_t pin_green, uint8_t pin_blue)
{
#ifdef __DEBUG__
    Serial.print("rgb led pin R: ");
    Serial.println(pin_red);
    Serial.print("rgb led pin G: ");
    Serial.println(pin_green);
    Serial.print("rgb led pin B: ");
    Serial.println(pin_blue);
#endif

    color_pins.red = pin_red;
    color_pins.green = pin_green;
    color_pins.blue = pin_blue;
    pinMode(pin_red, OUTPUT);
    pinMode(pin_green, OUTPUT);
    pinMode(pin_blue, OUTPUT);
    setColor(0x0, 0x0, 0x0);
}

Color RGBLEDDriver::getColor()
{
    return color;
}

void RGBLEDDriver::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
#ifdef __DEBUG__
    Serial.print("rgb led R: ");
    Serial.println(red);
    Serial.print("rgb led G: ");
    Serial.println(green);
    Serial.print("rgb led B: ");
    Serial.println(blue);
#endif

    color.red = red;
    color.green = green;
    color.blue = blue;
    analogWrite(color_pins.red, red);
    analogWrite(color_pins.green, green);
    analogWrite(color_pins.blue, blue);
}

void RGBLEDDriver::cycle() {}

RGBLEDDriver::~RGBLEDDriver() {}