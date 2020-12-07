#include <vector>
#include <Arduino.h>
#include <Display.h>
#include <Keypad.h>
#include <Watchdog.h>

#ifdef __H_BRIDGE_MOTOR__
#include <MotorBridge.h>
#else
#include <MotorRelay.h>
#endif

#ifdef __RGB_LED__
#include <RGBLEDDriver.h>
#endif

#define ENCODER_PIN_CLK 2
#ifdef __RGB_LED__
#define ENCODER_PIN_DIO 12
#else
#define ENCODER_PIN_DIO 3
#endif
#define DISPLAY_PIN_CLK 4
#define DISPLAY_PIN_DIO 5

#ifdef __RGB_LED__
#define LED_PIN_RED 3
#define LED_PIN_GREEN 6
#define LED_PIN_BLUE 11
#endif

#define DIRECTION_RELAY 6
#define POWER_RELAY 7

#define R_EN 7
#define L_EN 8
#define R_PWM 9
#define L_PWM 10

static std::vector<Service *> services;

#ifdef __EEPROM__

bool eeprom_valid()
{
    for (unsigned int i = ADDRESS_MODE + 4 * sizeof(unsigned int); i < EEPROM.length(); ++i)
    {
        if (EEPROM[i] != 0)
        {
            return false;
        }
    }
    return true;
}

void eeprom_reset()
{
#ifdef __DEBUG__
    Serial.println("reset eeprom");
#endif
    for (unsigned int i = 0; i < EEPROM.length(); ++i)
        updateEEPROM(i, 0);
}

#endif

void setup()
{
#ifdef __DEBUG__
    Serial.begin(9600);
#endif
#ifdef __EEPROM__
    if (!eeprom_valid())
        eeprom_reset();
#endif

    delay(1000);
#ifdef __H_BRIDGE_MOTOR__
    auto motor = new MotorBridge(ENCODER_PIN_CLK, ENCODER_PIN_DIO, R_EN, L_EN, R_PWM, L_PWM);
#else
    auto motor = new MotorRelay(ENCODER_PIN_CLK, ENCODER_PIN_DIO, POWER_RELAY, DIRECTION_RELAY);
#endif
    auto display = new Display(DISPLAY_PIN_CLK, DISPLAY_PIN_DIO);

    services.push_back((Service *)new Watchdog(motor, display));
    services.push_back((Service *)new Keypad(motor, display));
    services.push_back((Service *)motor);
    services.push_back((Service *)display);
    services.push_back((Service *)NIButtons::get_instance());
#ifdef __RGB_LED__
    services.push_back((Service *)new RGBLEDDriver(LED_PIN_RED, LED_PIN_GREEN, LED_PIN_BLUE));
#endif

#ifdef __DEBUG__
    Serial.println("starting");
#endif
}

void loop()
{
    for (const auto &service : services)
    {
        service->cycle();
    }
}