#include "Controllers/SetSettingsController.h"

SetSettingsController::SetSettingsController() {}

void SetSettingsController::invoke(int startHour, int endHour) {
    Settings& settings = Settings::getInstance();

    if (startHour < 24 && startHour >=0 && endHour < 24 && endHour >=0) {
        settings.startNightHourInterval = startHour;
        settings.endNightHourInterval = endHour;
    }
}
