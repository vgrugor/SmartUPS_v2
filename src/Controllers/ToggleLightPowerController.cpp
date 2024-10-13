#include "Controllers/ToggleLightPowerController.h"

ToggleLightPowerController::ToggleLightPowerController() {}

void ToggleLightPowerController::invoke() {
    DigitalOutputPin lightPowerPin(LIGHT_POWER_CONTROL_PIN);
    Scheduler& scheduler = Scheduler::getInstance();
    Settings& settings = Settings::getInstance();

    if (settings.isOnLightPower) {
        lightPowerPin.turnOff();
        settings.isOnLightPower = false;

        scheduler.removeTask(DisableLightPowerTask::TASK_NAME);
    } else {
        lightPowerPin.turnOn();
        settings.isOnLightPower = true;
    }
}
