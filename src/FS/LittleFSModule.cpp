#include "FS/LittleFSModule.h"

LittleFSModule::LittleFSModule() {}

void LittleFSModule::begin() {
    if (!LittleFS.begin()) {
        //Serial.println("Ошибка монтирования LittleFS");
        return;
    }
    //Serial.println("LittleFS смонтирована успешно");
}

bool LittleFSModule::exists(const String& path) {
    return LittleFS.exists(path.c_str());
}

File LittleFSModule::open(const String& path, const char* mode) {
    return LittleFS.open(path.c_str(), mode);
}
