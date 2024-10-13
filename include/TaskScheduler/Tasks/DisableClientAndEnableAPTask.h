#ifndef DISABLECLIENTANDENABLEAPTASK_H
    #define DISABLECLIENTANDENABLEAPTASK_H

    #include <Arduino.h>
    #include "TaskScheduler/Task.h"
    #include "WiFi/WifiManager.h"

    class DisableClientAndEnableAPTask : public Task {
        public:
            DisableClientAndEnableAPTask(unsigned long delayMs, bool isUnique = false);
            void execute() override;
            static const char* const TASK_NAME;
    };

#endif
