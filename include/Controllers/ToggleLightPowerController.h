#ifndef TOGGLELIGHTPOWERCONTROLLER_H
    #define TOGGLELIGHTPOWERCONTROLLER_H

    #include "config/defines.h"
    #include "Settings/Settings.h"
    #include "gpio/DigitalOutputPin.h"
    #include "TaskScheduler/Scheduler.h"
    #include "TaskScheduler/Tasks/DisableLightPowerTask.h"

    class ToggleLightPowerController {
        public:
            ToggleLightPowerController();
            static void invoke();
    };

#endif
