#include "Controllers/ToggleLightPowerController.h"

ToggleLightPowerController::ToggleLightPowerController() {}

void ToggleLightPowerController::invoke() {
    DigitalOutputPin lightPowerPin(LIGHT_POWER_CONTROL_PIN);
    TaskManager& taskManager = TaskManager::getInstance();
    Settings& settings = Settings::getInstance();

    if (settings.isOnLightPower) {
        lightPowerPin.turnOff();
        settings.isOnLightPower = false;

        int taskIndex = taskManager.findTaskByName(DisableLightPowerTask::TASK_NAME);

        if (taskIndex != -1) {
            taskManager.removeTask(taskIndex);
        }
    } else {
        lightPowerPin.turnOn();
        settings.isOnLightPower = true;
    }
}
