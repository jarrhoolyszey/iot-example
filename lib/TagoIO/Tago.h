#ifndef TAGOIO_H
#define TAGOIO_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>


// TagoIO API Configs
#define TAGO_BASE_URL "http://api.tago.io"
#define ESP8266_TOKEN "6572a280-7451-4fb3-acee-7118ed7da957"

// DHT Sensor Configs
#define DHT_PIN   D1
#define DHT_TYPE  DHT22


// Class definitios 
class TagoDevice {
  public:
    TagoDevice(String token);
    virtual void JsonData(String &output);
    String token(void) { return _device_token; };

  private:
    String _device_token;
};

class TagoClient {
  public:
    TagoClient(){};
    void SendData(TagoDevice &device);
    int GetMotorAngle(void);

  private:
    String _BASE_URL = TAGO_BASE_URL;
    HTTPClient http;
    WiFiClient client;
};

class DHT_Device : public DHT, public TagoDevice {
  public:
    DHT_Device(uint8_t pin, uint8_t type, String token);
    void JsonData(String &output);
};

#endif