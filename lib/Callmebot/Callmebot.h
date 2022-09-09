#ifndef CALLMEBOT_H
#define CALLMEBOT_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h>

class Callmebot {
  public:
    Callmebot(String phone, String api_key);
    String sendMessage(String msg);

  private:
    const String _base_url = "http://api.callmebot.com/whatsapp.php";
    String _phone;
    String _api_key;

    String generateUrl(String msg);
    String urlEncode(String str);
};

#endif