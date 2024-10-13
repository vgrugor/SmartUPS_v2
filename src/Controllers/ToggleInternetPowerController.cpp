#include "Controllers/ToggleInternetPowerController.h"

ToggleInternetPowerController::ToggleInternetPowerController() {}

void ToggleInternetPowerController::invoke() {
    DigitalOutputPin mediaConverterPowerPin(MEDIA_CONVERTER_POWER_CONTROL_PIN);
    DigitalOutputPin routerPowerPin(ROUTER_POWER_CONTROL_PIN);

    Settings& settings = Settings::getInstance();
    WifiManager& wifiManager = WifiManager::getInstance();
    Scheduler& scheduler = Scheduler::getInstance();

    if (settings.isOnMediaConverterPower) {
        mediaConverterPowerPin.turnOff();
        routerPowerPin.turnOff();

        wifiManager.disconnect();

        settings.isOnMediaConverterPower = false;
        settings.isOnRouterPower = false;

        wifiManager.connect();

        scheduler.removeTask(DisableInternetPowerTask::TASK_NAME);
    } else {
        mediaConverterPowerPin.turnOn();
        routerPowerPin.turnOn();

        wifiManager.disconnect();

        settings.isOnMediaConverterPower = true;
        settings.isOnRouterPower = true;

        wifiManager.connect();

        int powerOffTime = settings.hours + 1;

        if (
            !settings.isMainPower
            && TimeService::timeInInterval(settings.startNightHourInterval, settings.endNightHourInterval, powerOffTime)
        ) {
            Serial.println("Create task");
            DisableInternetPowerTask disableInternetPowerTask(60 * 60 * 1000, true);
            Serial.println("Task created");
            Serial.println("Start add task");
            scheduler.addTask(&disableInternetPowerTask);
            Serial.println("Task added");
        }
    }
}
