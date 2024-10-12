#ifndef DISABLEINTERNETPOWERTASK_H
    #define DISABLEINTERNETPOWERTASK_H

    #include <Arduino.h>
    #include "TaskScheduler/Task.h"
    #include "gpio/DigitalOutputPin.h"
    #include "Settings/Settings.h"
    #include "WiFi/WifiManager.h"

    class DisableInternetPowerTask : public Task {
        public:
            DisableInternetPowerTask(unsigned long taskDelay, bool unique = false);
            void execute() override;
            static const char* const TASK_NAME;
    };

#endif
