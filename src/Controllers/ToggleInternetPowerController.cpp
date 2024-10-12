#include "Controllers/ToggleInternetPowerController.h"

ToggleInternetPowerController::ToggleInternetPowerController() {}

void ToggleInternetPowerController::invoke() {
    DigitalOutputPin mediaConverterPowerPin(MEDIA_CONVERTER_POWER_CONTROL_PIN);
    DigitalOutputPin routerPowerPin(ROUTER_POWER_CONTROL_PIN);

    Settings& settings = Settings::getInstance();
    WifiManager& wifiManager = WifiManager::getInstance();
    TaskManager& taskManager = TaskManager::getInstance();

    if (settings.isOnMediaConverterPower) {
        mediaConverterPowerPin.turnOff();
        routerPowerPin.turnOff();

        wifiManager.disconnect();

        settings.isOnMediaConverterPower = false;
        settings.isOnRouterPower = false;

        wifiManager.connect();

        int taskIndex = taskManager.findTaskByName(DisableInternetPowerTask::TASK_NAME);

        if (taskIndex != -1) {
            taskManager.removeTask(taskIndex);
        }
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
            DisableInternetPowerTask disableInternetPowerTask(60 * 60 * 1000, true);
            taskManager.addTask(&disableInternetPowerTask);
        }
    }
}
