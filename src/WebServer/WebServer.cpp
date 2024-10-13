#include "WebServer/WebServer.h"

WebServer::WebServer(
    LittleFSModule &littleFSModule,
    ToggleInternetPowerController &toggleInternetPowerController
) : server(80),
    littleFSModule(littleFSModule),
    toggleInternetPowerController(toggleInternetPowerController)
{}

void WebServer::begin() {
    this->server.on("/", HTTP_GET, std::bind(&WebServer::handleRoot, this));
    this->server.on("/api/status", HTTP_GET, std::bind(&WebServer::getStatus, this));
    this->server.on("/api/toggleInternetPower", HTTP_POST, std::bind(&WebServer::handleToggleInternetPower, this));
    this->server.on("/api/toggleLightPower", HTTP_POST, std::bind(&WebServer::handleToggleLightPower, this));
    this->server.on("/api/setTime", HTTP_POST, std::bind(&WebServer::handleSetTime, this));
    this->server.on("/api/setSettings", HTTP_POST, std::bind(&WebServer::handleSetSettings, this));
    this->server.onNotFound(std::bind(&WebServer::handleNotFound, this));
    this->server.begin();
}

void WebServer::handleClient() {
    this->server.handleClient();
}

void WebServer::handleRoot() {
    Serial.println("WebServer::handleRoot()");

    File file = this->littleFSModule.open("/index.html", "r");

    if (!file) {
        this->server.send(500, "text/plain", "File not found");

        return;
    }

    this->server.streamFile(file, "text/html");
    file.close();
}

void WebServer::handleNotFound() {
    if (this->littleFSModule.exists(this->server.uri())) {
        File file = this->littleFSModule.open(this->server.uri(), "r");

        if (file) {
            String contentType = "text/plain";
            if (this->server.uri().endsWith(".html")) contentType = "text/html";
            else if (this->server.uri().endsWith(".css")) contentType = "text/css";
            else if (this->server.uri().endsWith(".js")) contentType = "application/javascript";
            else if (this->server.uri().endsWith(".png")) contentType = "image/png";
            else if (this->server.uri().endsWith(".jpg") || this->server.uri().endsWith(".jpeg")) contentType = "image/jpeg";

            this->server.streamFile(file, contentType);
            file.close();

            return;
        }
    }
    this->server.send(404, "text/plain", "Not Found");
}

void WebServer::successResponse() {
    Serial.println("WebServer::successResponse() get settings");
    Settings& settings = Settings::getInstance();
    Serial.println("WebServer::successResponse() setting getted");

    Serial.println("start get JSON");
    String js = settings.toJSON();
    Serial.println("JSON getted");

    Serial.println("Start send response");
    this->server.send(200, "application/json", settings.toJSON());
    Serial.println("Response sended");
}

void WebServer::handleToggleInternetPower() {
    this->toggleInternetPowerController.execute();

    this->successResponse();
}

void WebServer::handleToggleLightPower() {
    ToggleLightPowerController::invoke();

    this->successResponse();
}

void WebServer::handleSetTime() {
    if (
        this->server.hasArg("hour") 
        && this->server.hasArg("minute")
        && this->server.arg("hour").toInt() < 24 
        && this->server.arg("hour").toInt() >=0 
        && this->server.arg("minute").toInt() < 60 
        && this->server.arg("minute").toInt() >= 0
    ) {
        int hour = this->server.arg("hour").toInt();
        int minute = this->server.arg("minute").toInt();

        SetTimeController::invoke(hour, minute);

        this->successResponse();
    } else {
        this->errorResponse();
    }
}

void WebServer::handleSetSettings() {
    if (
        this->server.hasArg("startHour") 
        && this->server.hasArg("endHour")
        && this->server.arg("startHour").toInt() < 24 
        && this->server.arg("startHour").toInt() >=0 
        && this->server.arg("endHour").toInt() < 24 
        && this->server.arg("endHour").toInt() >=0 
    ) {
        int startHour = this->server.arg("startHour").toInt();
        int endHour = this->server.arg("endHour").toInt();

        SetSettingsController::invoke(startHour, endHour);

        this->successResponse();
    } else {
        this->errorResponse();
    }
}

void WebServer::errorResponse() {
    this->server.send(400, "text/plain", "Invalid parameters");
}

void WebServer::getStatus() {
    this->successResponse();
}
