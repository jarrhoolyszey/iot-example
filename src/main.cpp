#include <Arduino.h>
#include <IOTExample.h>
#include <Tago.h>
#include <Servo.h>

DHT_Device dht22(DHT_PIN, DHT_TYPE, ESP8266_TOKEN);
TagoClient tago;
Servo servo;
uint16_t sg90_min = 500;
uint16_t sg90_max = 2300;

unsigned long tago_request_interval = 60 * 1000; // 60s
unsigned long tago_last_request = 0;

unsigned long servo_request_interval = 3 * 1000;
unsigned long servo_last_request = 0; 


void setup() {
  servo.attach(13, sg90_min, sg90_max);

  setupSerial();
  setupWiFi();

  dht22.begin();
}

void loop() {
  if(millis() - tago_last_request > tago_request_interval) {
    tago.SendData(dht22);
    tago_last_request = millis();
  }

  if(millis() - servo_last_request > servo_request_interval) {
    int angle = tago.GetMotorAngle();

    if(angle >= 0 && angle <= 180 && angle != servo.read()) {
      servo.write(angle);
    }

    servo_last_request = millis();
  }  
      
    

    
  

  // servo.write(sg90_min);
  // delay(2000);
  // servo.write(1300);
  // delay(2000);
  // servo.write(sg90_max);
  // delay(2000);
}