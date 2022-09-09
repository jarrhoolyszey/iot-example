#include "Tago.h"


/* TagoDevice Methods  */
TagoDevice::TagoDevice(String token){
  _device_token = token;
}

void TagoDevice::JsonData(String &output) {
  return;
}

/* TagoClient Methods */
void TagoClient::SendData(TagoDevice &device) {

  http.begin(client, _BASE_URL + "/data");
  http.addHeader("device-token", device.token());
  http.addHeader("content-type", "application/json");
  
  String body;
  device.JsonData(body);

  if (body.isEmpty()) {
    Serial.println(F("[TAGO.IO] Invalid body data."));
    return;
  }

  int httpCode = http.POST(body);

  if(httpCode > 0) {
    Serial.printf("[TAGO.IO] POST... code: %d\n", httpCode );

    if(httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_ACCEPTED) {
      const String &payload = http.getString();
      Serial.println(F("received payload:\n<<"));
      Serial.println(payload);
      Serial.println(F(">>"));
    }

  }

  http.end();
}

int TagoClient::GetMotorAngle() {
  String url = _BASE_URL + "/data?";
  url = url + "variable=servo_angle";
  url = url + "&query=last_item";
  url = url + "&details=false";

  http.begin(client, url);
  http.addHeader("device-token", ESP8266_TOKEN);
  
  int httpCode = http.GET();

  if(httpCode < 0) {
    Serial.println("Request error - code: " + httpCode);
    return -1;
  }

  StaticJsonDocument<512> doc;

  DeserializationError error = deserializeJson(doc, http.getStream());

  if(error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return 0.0;
  }

  JsonObject payload = doc["result"][0];
  int angle = payload["value"];
  
  http.end();

  return angle;
}


/* DHT Device Methods */
DHT_Device::DHT_Device(uint8_t pin, uint8_t type, String token):
  DHT(pin, type),
  TagoDevice(token) {};

void DHT_Device::JsonData(String &output) {
  // Read sensors
  float t = readTemperature();
  float h = readHumidity();  
  

  if (isnan(t) || isnan(h)) {
    Serial.println(F("[DHT_Device] Error - Cannot read sensors."));
    return;
  }

  // Generate JSON Data for Tago API
  StaticJsonDocument<256> doc;

  JsonObject doc_0 = doc.createNestedObject();
  doc_0["variable"] = "temperature";
  doc_0["value"] = (t * 10) / 10.0; // only to crop decimal
  doc_0["unit"] = "C";

  JsonObject doc_1 = doc.createNestedObject();
  doc_1["variable"] = "humidity";
  doc_1["value"] = (h * 10) / 10.0;
  doc_1["unit"] = "%";

  output = "";

  serializeJson(doc, output);
}