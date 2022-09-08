#include <IOTExample.h>


WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;


void setupSerial() {
  Serial.begin(9600);
  while(!Serial);
}

void setupWiFi() {
  gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP &event)
  {
    Serial.print("[WiFi] Connected, IP: ");
    Serial.println(WiFi.localIP());
  });

  disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected &event) {
    Serial.println("[WiFi] Disconnected");
  });

  Serial.println("[WiFi] Connecting to " + WiFi.SSID());
  WiFi.begin(WIFI_SSID, WIFI_PSWD);
  
  WiFi.setAutoReconnect(true);
}
