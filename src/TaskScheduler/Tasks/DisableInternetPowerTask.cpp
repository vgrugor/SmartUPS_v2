#include "TaskScheduler/Tasks/DisableInternetPowerTask.h"

const char* const DisableInternetPowerTask::TASK_NAME = "disable_internet_power";

DisableInternetPowerTask::DisableInternetPowerTask(
    unsigned long delayMs, 
    bool unique
) 
    : Task(DisableInternetPowerTask::TASK_NAME, delayMs, unique)
{}

void DisableInternetPowerTask::execute() {
    DigitalOutputPin mediaConverterPowerPin(MEDIA_CONVERTER_POWER_CONTROL_PIN);
    DigitalOutputPin routerPowerPin(ROUTER_POWER_CONTROL_PIN);

    Settings& settings = Settings::getInstance();
    WifiManager& wifiManager = WifiManager::getInstance();

    mediaConverterPowerPin.turnOff();
    routerPowerPin.turnOff();

    wifiManager.disconnectClient();

    settings.isOnMediaConverterPower = false;
    settings.isOnRouterPower = false;

    wifiManager.enableAP();
}
