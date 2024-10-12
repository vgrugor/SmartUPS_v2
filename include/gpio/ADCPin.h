#pragma once

#include "Pin.h"

class ADCPin : public Pin {
    public:
        ADCPin(uint8_t pin);
        void init() override;
        uint16_t read() const;
};
