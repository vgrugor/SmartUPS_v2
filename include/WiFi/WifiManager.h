#ifndef WIFIMANAGER_H
    #define WIFIMANAGER_H

    #include <ESP8266WiFi.h>
    #include <ESP8266WiFi.h>
    #include "config/defines.h"
    #include "Settings/Settings.h"
    #include "WiFi/AccessPoint.h"
    #include "WiFi/WifiClient.h"

    class WifiManager {
        public:
            static WifiManager& getInstance();
            void handle();
            void disconnectClient();
            void disableAP();
            void connectClient();
            void enableAP();

        private:
            WifiManager(
                const char* ssidSTA = WIFI_SSID_STA,
                const char* passwordSTA = WIFI_PASS_STA, 
                const char* ssidAP = WIFI_SSID_AP,
                const char* passwordAP = WIFI_PASS_AP, 
                IPAddress local_ip = IPAddress(192, 168, 1, 210),
                IPAddress gateway = IPAddress(192, 168, 1, 1),
                IPAddress subnet = IPAddress(255, 255, 255, 0)
            );
            ~WifiManager() = default;
            WifiManager(const WifiManager&) = delete;
            WifiManager& operator=(const WifiManager&) = delete;
            const char* ssidSTA;
            const char* passwordSTA;
            const char* ssidAP;
            const char* passwordAP;
            IPAddress local_ip;
            IPAddress gateway;
            IPAddress subnet;
            Settings &settings;
            AccessPoint accessPoint;
            WifiClient wifiClient;
    };

#endif
