#include "Controllers/ToggleInternetPowerController.h"

ToggleInternetPowerController::ToggleInternetPowerController(
    Settings &settings,
    WifiManager &wifiManager,
    Scheduler &scheduler
) : mediaConverterPowerPin(DigitalOutputPin(MEDIA_CONVERTER_POWER_CONTROL_PIN)),
    routerPowerPin(DigitalOutputPin(ROUTER_POWER_CONTROL_PIN)),
    settings(settings),
    wifiManager(wifiManager),
    scheduler(scheduler)
{}

void ToggleInternetPowerController::execute() {
    if (this->settings.isOnMediaConverterPower) {
        this->mediaConverterPowerPin.turnOff();
        this->routerPowerPin.turnOff();

        //this->wifiManager.disconnectClient();

        this->settings.isOnMediaConverterPower = false;
        this->settings.isOnRouterPower = false;

        //this->wifiManager.enableAP();

        //this->scheduler.removeTask(DisableInternetPowerTask::TASK_NAME);

        Serial.println("Create task class DisableClientAndEnableAPTask");
        DisableClientAndEnableAPTask disableClientAndEnableAPTask(2 * 1000, true);
        Serial.println("DisableClientAndEnableAPTask task class created");

        Serial.println("Add task DisableClientAndEnableAPTask to scheduler");
        this->scheduler.addTask(&disableClientAndEnableAPTask);
        Serial.println("DisableClientAndEnableAPTask added to scheduler");
    } else {
        this->mediaConverterPowerPin.turnOn();
        this->routerPowerPin.turnOn();

        //this->wifiManager.disableAP();

        this->settings.isOnMediaConverterPower = true;
        this->settings.isOnRouterPower = true;

        //this->wifiManager.connectClient();

        int powerOffTime = settings.hours + 1;

        if (
            !this->settings.isMainPower
            && TimeService::timeInInterval(this->settings.startNightHourInterval, this->settings.endNightHourInterval, powerOffTime)
        ) {
            DisableInternetPowerTask disableInternetPowerTask(60 * 60 * 1000, true);
            this->scheduler.addTask(&disableInternetPowerTask);
        }

        DisableAPAndEnableClientTask disableAPAndEnableClientTask(2 * 1000, true);
        this->scheduler.addTask(&disableAPAndEnableClientTask);
    }
}
