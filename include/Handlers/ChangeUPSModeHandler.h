#ifndef CHANGEUPSMODEHANDLER_H
    #define CHANGEUPSMODEHANDLER_H

    #include "Settings/Settings.h"
    #include "gpio/DigitalInputPin.h"
    #include "config/defines.h"
    #include "gpio/DigitalOutputPin.h"
    #include "TaskScheduler/TaskManager.h"
    #include "TaskScheduler/Tasks/DisableLightPowerTask.h"

    class ChangeUPSModeHandler {
        public:
            ChangeUPSModeHandler();
            void handle();
    };

#endif
