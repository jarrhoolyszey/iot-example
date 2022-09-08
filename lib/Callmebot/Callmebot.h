#ifndef CALLMEBOT_H
#define CALLMEBOT_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h>

extern String generate_url(String msg);
extern String url_encode(String str);
extern String send_message(String msg);

#endif