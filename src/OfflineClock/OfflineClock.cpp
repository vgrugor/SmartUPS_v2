#include "OfflineClock/OfflineClock.h"

OfflineClock::OfflineClock() : lastMillis(millis()) {}

void OfflineClock::begin() {
    this->lastMillis = millis();
}

void OfflineClock::refresh() {
    unsigned long currentMillis = millis();
    unsigned long elapsedTime = this->calculateElapsedTime(currentMillis);
    Settings& settings = Settings::getInstance();

    //if (elapsedTime >= 60000) {
    if (elapsedTime >= 1000) {
        settings.minutes++;

        if (settings.minutes > 59) {
            settings.minutes = 0;
            settings.hours++;

            if (settings.hours > 23) {
                settings.hours = 0;
            }
        }

        this->lastMillis = currentMillis;
    }
}

unsigned long OfflineClock::calculateElapsedTime(unsigned long currentMillis) const {
    return (currentMillis >= this->lastMillis) 
        ? (currentMillis - this->lastMillis) 
        : (ULONG_MAX - this->lastMillis + currentMillis + 1);
}
