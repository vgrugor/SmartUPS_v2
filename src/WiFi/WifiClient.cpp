#include "WiFi/WifiClient.h"

WifiClient::WifiClient(
    const char* ssid,
    const char* password, 
    IPAddress local_ip, 
    IPAddress gateway, 
    IPAddress subnet
) : ssid(ssid), password(password), local_ip(local_ip), gateway(gateway), subnet(subnet) {}

void WifiClient::connect() {
    WiFi.mode(WIFI_STA);
    WiFi.config(this->local_ip, this->gateway, this->subnet);
    WiFi.begin(ssid, password);

    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED/* && millis() - startTime < 180000*/) {
        delay(1000);
        Serial.println("connect to wifi");
    }
}


void WifiClient::disconnect() {
    WiFi.disconnect();
}

void WifiClient::reconnect() {
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
}
