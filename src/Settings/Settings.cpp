#include "Settings/Settings.h"

Settings& Settings::getInstance() {
    static Settings instance;
    return instance;
}

Settings::Settings() {}

void Settings::begin() {
    DigitalInputPin mainPowerPin(POWER_SENSE_PIN);
    mainPowerPin.init();
    this->isMainPower = mainPowerPin.isHigh();

    this->batteryPercent = 0.00;
    this->batteryVoltage = 0.00;

    DigitalOutputPin mediaConverterPower(MEDIA_CONVERTER_POWER_CONTROL_PIN);
    mediaConverterPower.init();
    mediaConverterPower.turnOn();
    this->isOnMediaConverterPower = mediaConverterPower.isOn();

    DigitalOutputPin routerPowerPin(ROUTER_POWER_CONTROL_PIN);
    routerPowerPin.init();
    routerPowerPin.turnOn();
    this->isOnRouterPower = routerPowerPin.isOn();

    DigitalOutputPin lightPowerPin(LIGHT_POWER_CONTROL_PIN);
    lightPowerPin.init();
    lightPowerPin.turnOff();
    this->isOnLightPower = lightPowerPin.isOn();

    this->hours = 0;
    this->minutes = 0;
    this->startNightHourInterval = 0;
    this->endNightHourInterval = 7;
}

String Settings::toJSON() {
    String json = "{";
    json += "\"powerSource\":\"" + String(this->isMainPower ? "mains" : "battery") + "\",";
    json += "\"batteryLevel\":" + String(this->batteryPercent) + ",";
    json += "\"batteryVoltage\":" + String(this->batteryVoltage) + ",";
    json += "\"mediaConverterState\":\"" + String(this->isOnMediaConverterPower ? "on" : "off") + "\",";
    json += "\"routerState\":\"" + String(this->isOnRouterPower ? "on" : "off") + "\",";
    json += "\"lightState\":\"" + String(this->isOnLightPower ? "on" : "off") + "\",";
    json += "\"currentHour\":" + String(this->hours) + ",";
    json += "\"currentMinute\":" + String(this->minutes) + ",";
    json += "\"startNightHourInterval\":" + String(this->startNightHourInterval) + ",";
    json += "\"endNightHourInterval\":" + String(this->endNightHourInterval);
    json += "}";

   return json;
}
