#include "TaskScheduler/Tasks/DisableClientAndEnableAPTask.h"

const char* const DisableClientAndEnableAPTask::TASK_NAME = "disable_client_and_enable_AP";

DisableClientAndEnableAPTask::DisableClientAndEnableAPTask(
    unsigned long delayMs, 
    bool unique
) 
    : Task(DisableClientAndEnableAPTask::TASK_NAME, delayMs, unique)
{}

void DisableClientAndEnableAPTask::execute() {
    WifiManager& wifiManager = WifiManager::getInstance();

    wifiManager.disconnectClient();
    wifiManager.enableAP();
}
