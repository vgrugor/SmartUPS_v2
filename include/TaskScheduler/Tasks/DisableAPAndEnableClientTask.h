#ifndef DISABLEAPANDENABLECLIENTTASK_H
    #define DISABLEAPANDENABLECLIENTTASK_H

    #include <Arduino.h>
    #include "TaskScheduler/Task.h"
    #include "WiFi/WifiManager.h"

    class DisableAPAndEnableClientTask : public Task {
        public:
            DisableAPAndEnableClientTask(unsigned long delayMs, bool isUnique = false);
            void execute() override;
            static const char* const TASK_NAME;
    };

#endif
