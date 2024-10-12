#ifndef OFFLINECLOCK_H
    #define OFFLINECLOCK_H

    #include <climits>
    #include "Settings/Settings.h"

    class OfflineClock {
        public:
            OfflineClock();
            void begin();
            void refresh();

        private:
            unsigned long lastMillis;
            int hours;
            int minutes;
            unsigned long calculateElapsedTime(unsigned long currentMillis) const;
    };

#endif
