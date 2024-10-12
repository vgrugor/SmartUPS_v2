#include "utils/TimeService.h"

TimeService::TimeService() {}

bool TimeService::isElapsedTime(unsigned long timeMillis) {
    return timeMillis <= millis();
}

bool TimeService::getCorrectedTime(unsigned long intervalMillis) {
    unsigned long currentTimeMillis = millis();

    if ((ULONG_MAX - currentTimeMillis) < intervalMillis) {    
        return intervalMillis - (ULONG_MAX - currentTimeMillis);
    }

    return currentTimeMillis + intervalMillis;
}

bool TimeService::timeInInterval(int startHour, int endHour, int currentHour) {
    return (startHour <= endHour && currentHour >= startHour && currentHour < endHour)
        || (startHour > endHour && (currentHour >= startHour || currentHour < endHour));
}
