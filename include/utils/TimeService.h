#ifndef TIMESERVICE_H
    #define TIMESERVICE_H

    #include <Arduino.h>
    #include <climits>

    class TimeService {
        public:
            TimeService();
            static bool isElapsedTime(unsigned long timeMillis);
            static bool getCorrectedTime(unsigned long currentMillis);
            static bool timeInInterval(int startInterval, int endInterval, int hour);
        private:
            unsigned long lastMillis;
    };

#endif
