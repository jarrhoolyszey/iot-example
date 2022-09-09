#ifndef IOTEXAMPLE_H
#define IOTEXAMPLE_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Tago.h>
#include <Servo.h>
#include <Callmebot.h>

// Reed Switch Configs
#define REED_SWITCH_PIN D2

// Servo Motor Onfigs
#define SERVO_PIN           D7
#define SERVO_MIN           500
#define SERVO_MAX           2300

// Timers intervals
#define SERVO_REQUEST_INTERVAL  5000  // 5 seconds
#define DHT_REQUEST_INTERVAL    60000 // 60 seconds    

// WiFi event variables
extern WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;

// ReedSwitch variables
extern bool reed_changed, reed_last_status; 

void setupSerial(void);
void setupWiFi(void);
void setupReedSwitch(void);
void reedSwitchHandler(void);

void IRAM_ATTR ISR_ReedSwitch(void);


#endif