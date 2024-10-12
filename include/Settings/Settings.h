#ifndef SETTINGS_H
    #define SETTINGS_H

    #include <Arduino.h>
    #include <map>
    #include "gpio/DigitalInputPin.h"
    #include "config/defines.h"
    #include "gpio/DigitalOutputPin.h"

    class Settings {
        public:
            static Settings& getInstance();
            void initializeData();
            void begin();
            bool isMainPower;
            float batteryPercent;
            float batteryVoltage;
            bool isOnMediaConverterPower;
            bool isOnRouterPower;
            bool isOnLightPower;
            int hours;
            int minutes;
            int startNightHourInterval;
            int endNightHourInterval;
            String toJSON();

        private:
            Settings();
            ~Settings() = default;
            Settings(const Settings&) = delete;
            Settings& operator=(const Settings&) = delete;
    };

#endif
