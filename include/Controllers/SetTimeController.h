#ifndef SETTIMECONTROLLER_H
    #define SETTIMECONTROLLER_H

    #include "Settings/Settings.h"
    

    class SetTimeController {
        public:
            SetTimeController();
            static void invoke(int hour, int minute);
    };

#endif
