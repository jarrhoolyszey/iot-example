#include <IOTExample.h>


WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;

Callmebot callmebot(CMB_PHONE, CMB_API_KEY);

bool reed_changed = false;
bool reed_last_status;


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

void setupReedSwitch() {
  pinMode(REED_SWITCH_PIN, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(REED_SWITCH_PIN),
    ISR_ReedSwitch,
    CHANGE
  );

  interrupts();

  reed_last_status = digitalRead(REED_SWITCH_PIN);
}

void reedSwitchHandler() {
  bool reed_curr_status = digitalRead(REED_SWITCH_PIN); 
  if(reed_curr_status != reed_last_status) {
    String msg = "Reed switch was ";
    msg += reed_curr_status ? "opened" : "closed";
    
    callmebot.sendMessage(msg);
  }

  reed_last_status = reed_curr_status;
  reed_changed = false;
}

void IRAM_ATTR ISR_ReedSwitch() {
  reed_changed = true;
}