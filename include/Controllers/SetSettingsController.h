#ifndef SETSETTINGSCONTROLLER_H
    #define SETSETTINGSCONTROLLER_H

    #include "Settings/Settings.h"

    class SetSettingsController {
        public:
            SetSettingsController();
            static void invoke(int startHour, int endHour);
    };

#endif
