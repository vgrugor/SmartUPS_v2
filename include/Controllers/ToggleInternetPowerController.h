#ifndef TOGGLEINTERNETPOWERCONTROLLER_H
    #define TOGGLEINTERNETPOWERCONTROLLER_H

    #include "config/defines.h"
    #include "Settings/Settings.h"
    #include "gpio/DigitalOutputPin.h"
    #include "WiFi/WifiManager.h"
    #include "utils/TimeService.h"
    #include "TaskScheduler/Scheduler.h"
    #include "TaskScheduler/Tasks/DisableInternetPowerTask.h"
    #include "TaskScheduler/Tasks/DisableAPAndEnableClientTask.h"
    #include "TaskScheduler/Tasks/DisableClientAndEnableAPTask.h"

    class ToggleInternetPowerController {
        public:
            ToggleInternetPowerController(
                Settings &settings,
                WifiManager &wifiManager,
                Scheduler &scheduler
            );
            void execute();

        private:
            DigitalOutputPin mediaConverterPowerPin;
            DigitalOutputPin routerPowerPin;
            Settings &settings;
            WifiManager &wifiManager;
            Scheduler &scheduler;
    };

#endif
