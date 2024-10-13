#include "TaskScheduler/Tasks/DisableAPAndEnableClientTask.h"

const char* const DisableAPAndEnableClientTask::TASK_NAME = "disable_AP_and_enable_client";

DisableAPAndEnableClientTask::DisableAPAndEnableClientTask(
    unsigned long delayMs, 
    bool unique
) 
    : Task(DisableAPAndEnableClientTask::TASK_NAME, delayMs, unique)
{}

void DisableAPAndEnableClientTask::execute() {
    WifiManager& wifiManager = WifiManager::getInstance();

    wifiManager.disableAP();
    wifiManager.connectClient();
}
