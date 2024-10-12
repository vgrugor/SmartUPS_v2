#include "TaskScheduler/Tasks/DisableLightPowerTask.h"

const char* const DisableLightPowerTask::TASK_NAME = "disable_light_power";

DisableLightPowerTask::DisableLightPowerTask(
    unsigned long taskDelay, 
    bool unique
) 
    : Task(DisableLightPowerTask::TASK_NAME, delayTime, unique)
{}

void DisableLightPowerTask::execute() {
    DigitalOutputPin lightPowerPin(LIGHT_POWER_CONTROL_PIN);

    Settings& settings = Settings::getInstance();

    lightPowerPin.turnOff();

    settings.isOnLightPower = false;
}
