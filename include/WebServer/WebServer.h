#ifndef WEBSERVERMODULE_H
    #define WEBSERVERMODULE_H

    #include <ESP8266WebServer.h>
    #include <LittleFS.h>
    #include "FS/LittleFSModule.h"
    #include "Controllers/ToggleInternetPowerController.h"
    #include "Controllers/ToggleLightPowerController.h"
    #include "Controllers/SetTimeController.h"
    #include "Controllers/SetSettingsController.h"

    class WebServer {
        public:
            WebServer(
                LittleFSModule &littleFSModule
            );
            void begin();
            void handleClient();
        private:
            void handleRoot();
            void handleNotFound();
            void handleToggleInternetPower();
            void handleToggleLightPower();
            void handleSetTime();
            void handleSetSettings();
            void successResponse();
            void errorResponse();
            void getStatus();
            ESP8266WebServer server;
            LittleFSModule &littleFSModule;
    };

#endif
