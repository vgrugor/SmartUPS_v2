#ifndef TOGGLEINTERNETPOWERCONTROLLER_H
    #define TOGGLEINTERNETPOWERCONTROLLER_H

    #include "config/defines.h"
    #include "Settings/Settings.h"
    #include "gpio/DigitalOutputPin.h"
    #include "WiFi/WifiManager.h"
    #include "utils/TimeService.h"
    #include "TaskScheduler/Scheduler.h"
    #include "TaskScheduler/Tasks/DisableInternetPowerTask.h"

    class ToggleInternetPowerController {
        public:
            ToggleInternetPowerController();
            static void invoke();
    };

#endif
