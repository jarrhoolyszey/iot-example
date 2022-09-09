#include <Arduino.h>
#include <IOTExample.h>
#include <Tago.h>
#include <neotimer.h>

TagoClient tago;
DHT_Device dht22(DHT_PIN, DHT_TYPE, ESP8266_TOKEN);
Servo servo;

Neotimer DHT_Timer(DHT_REQUEST_INTERVAL);
Neotimer Servo_Timer(SERVO_REQUEST_INTERVAL);


void setup() {
  setupSerial();
  setupWiFi();
  setupReedSwitch();
  servo.attach(SERVO_PIN, SERVO_MIN, SERVO_MAX);
  
  dht22.begin();
}

void loop() {
  // Send DHT data to Tago.io
  if(DHT_Timer.repeat()) {
    tago.SendData(dht22);
  }

  // Check servo positioning
  if(Servo_Timer.repeat()) {
    int angle = tago.GetMotorAngle();

    if(angle >= 0 && angle <= 180 && angle != servo.read()) {
      servo.write(angle);
    }
  }

  // Check reed switch status
  if(reed_changed) {
    reedSwitchHandler();
  }
}