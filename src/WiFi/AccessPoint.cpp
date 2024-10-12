#include "WiFi/AccessPoint.h"

AccessPoint::AccessPoint(
    const char* ssid,
    const char* password, 
    IPAddress local_ip, 
    IPAddress gateway, 
    IPAddress subnet
) : ssid(ssid), password(password), local_ip(local_ip), gateway(gateway), subnet(subnet) {}

void AccessPoint::start() {
    WiFi.softAPConfig(local_ip, gateway, subnet);

    WiFi.softAP(ssid, password);
}

void AccessPoint::stop() {
    WiFi.softAPdisconnect(true);
}
