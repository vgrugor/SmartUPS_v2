#include "WiFi/WifiManager.h"

WifiManager::WifiManager(
    const char* ssidSTA,
    const char* passwordSTA, 
    const char* ssidAP,
    const char* passwordAP, 
    IPAddress local_ip, 
    IPAddress gateway, 
    IPAddress subnet
) : ssidSTA(ssidSTA),
    passwordSTA(passwordSTA),
    ssidAP(ssidAP),
    passwordAP(passwordAP),
    local_ip(local_ip),
    gateway(gateway),
    subnet(subnet),
    settings(Settings::getInstance()),
    accessPoint(AccessPoint(WIFI_SSID_AP, WIFI_PASS_AP, this->local_ip, this->gateway, this->subnet)),
    wifiClient(WifiClient(WIFI_SSID_STA, WIFI_PASS_STA, this->local_ip, this->gateway, this->subnet))
{}

WifiManager& WifiManager::getInstance() {
    static WifiManager instance;
    return instance;
}

void WifiManager::connect() {
    if (this->settings.isOnMediaConverterPower) {
        this->wifiClient.connect();
    } else {
        this->accessPoint.start();
    }
}

void WifiManager::disconnect() {
    if (this->settings.isOnMediaConverterPower) {
        this->wifiClient.disconnect();
    } else {
        this->accessPoint.stop();
    }
}

void WifiManager::handle() {
    if (this->settings.isOnMediaConverterPower) {
        this->wifiClient.reconnect();
    }
}
