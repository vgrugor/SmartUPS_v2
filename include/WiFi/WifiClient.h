#ifndef WIFICLIENT_H
    #define WIFICLIENT_H

    #include <ESP8266WiFi.h>
    #include <ESP8266WiFi.h>

    class WifiClient {
        public:
            WifiClient(
                const char* ssid,
                const char* password, 
                IPAddress local_ip = IPAddress(192, 168, 1, 210),
                IPAddress gateway = IPAddress(192, 168, 1, 1),
                IPAddress subnet = IPAddress(255, 255, 255, 0)
            );
            void connect();
            void disconnect();
            void reconnect();

        private:
            const char* ssid;
            const char* password;
            IPAddress local_ip;
            IPAddress gateway;
            IPAddress subnet;
    };

#endif
