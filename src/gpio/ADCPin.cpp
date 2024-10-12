#include "gpio/ADCPin.h"

ADCPin::ADCPin(uint8_t pin) : Pin(pin) {}

void ADCPin::init() {
    pinMode(_pin, INPUT);
}

uint16_t ADCPin::read() const {
    return analogRead(_pin);
}
