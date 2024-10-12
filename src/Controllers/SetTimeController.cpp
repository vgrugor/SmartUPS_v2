#include "Controllers/SetTimeController.h"

SetTimeController::SetTimeController() {}

void SetTimeController::invoke(int hour, int minute) {
    Settings& settings = Settings::getInstance();

    if (hour < 24 && hour >=0 && minute < 60 && minute >= 0) {
        settings.hours = hour;
        settings.minutes = minute;
    }
}
