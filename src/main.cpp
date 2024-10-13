#include "config/includes.h"
#include "config/defines.h"

Settings& settings = Settings::getInstance();
WifiManager& wifiManager = WifiManager::getInstance();
Scheduler& scheduler = Scheduler::getInstance();
LittleFSModule littleFSModule;

ToggleInternetPowerController toggleInternetPowerController(
	settings,
	wifiManager,
	scheduler
);

WebServer webServer(
	littleFSModule,
	toggleInternetPowerController
);
OfflineClock offlineClock;
ChangeUPSModeHandler changeUPSModeHandler;

void setup() {
	Serial.begin(115200);
	Serial.println("LOAD BOARD");
	settings.begin();
	wifiManager.connectClient();
	littleFSModule.begin();
	webServer.begin();
	offlineClock.begin();
}

void loop() {
	webServer.handleClient();
	offlineClock.refresh();
	wifiManager.handle();
	scheduler.executeTasks();
	changeUPSModeHandler.handle();
}
