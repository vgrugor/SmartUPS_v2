#ifndef DISABLELIGHTPOWERTASK_H
    #define DISABLELIGHTPOWERTASK_H

    #include <Arduino.h>
    #include "TaskScheduler/Task.h"
    #include "gpio/DigitalOutputPin.h"
    #include "Settings/Settings.h"

    class DisableLightPowerTask : public Task {
        public:
            DisableLightPowerTask(unsigned long delayMs, bool unique = false);
            void execute() override;
            static const char* const TASK_NAME;
    };

#endif
