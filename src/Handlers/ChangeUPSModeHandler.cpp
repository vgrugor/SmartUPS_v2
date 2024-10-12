#include "Handlers/ChangeUPSModeHandler.h"

ChangeUPSModeHandler::ChangeUPSModeHandler() {}

void ChangeUPSModeHandler::handle() {
    DigitalInputPin upsModePin(POWER_SENSE_PIN);
    DigitalOutputPin lightPowerPin(LIGHT_POWER_CONTROL_PIN);
    Settings& settings = Settings::getInstance();
    TaskManager& taskManager = TaskManager::getInstance();

    if (settings.isMainPower && upsModePin.isLow()) {
        settings.isMainPower = false;

        //TODO: handle day hours
        lightPowerPin.turnOn();

        DisableLightPowerTask disableLightPowerTask(60 * 1000, true);
        taskManager.addTask(&disableLightPowerTask);
    } else if (!settings.isMainPower && upsModePin.isHigh()) {
        settings.isMainPower = true;
    }
}
