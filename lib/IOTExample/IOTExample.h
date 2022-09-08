#ifndef IOTEXAMPLE_H
#define IOTEXAMPLE_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Tago.h>

// Reed Switch Configs
#define REED_SWITCH_PIN D1


// WiFi event variables
extern WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;

void setupSerial(void);
void setupWiFi(void);


#endif