#include "Callmebot.h"


Callmebot::Callmebot(String phone, String api_key){
  _phone = phone;
  _api_key = api_key;
}

String Callmebot::sendMessage(String msg) {
  Serial.println("[CALLMEBOT] Sending message to whatsapp");

  WiFiClient client;
  HTTPClient http;

  http.begin(client, generateUrl(msg));

  int httpCode = http.GET();

  if (httpCode < 0) {
    Serial.println("Callmebot request error - " + httpCode);
    return "";
  }

  String response = http.getString();

  http.end();

  return response;
}

String Callmebot::generateUrl(String msg) {
  String url = _base_url;
  url = url + "?phone=" + _phone;
  url = url + "&text=" + urlEncode(msg);
  url = url + "&apikey=" + _api_key;

  return url;
}

String Callmebot::urlEncode(String str) {
  String encodedString="";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i =0; i < str.length(); i++){
    c=str.charAt(i);
    if (c == ' '){
      encodedString+= '+';
    } else if (isalnum(c)){
      encodedString+=c;
    } else{
      code1=(c & 0xf)+'0';
      if ((c & 0xf) >9){
          code1=(c & 0xf) - 10 + 'A';
      }
      c=(c>>4)&0xf;
      code0=c+'0';
      if (c > 9){
          code0=c - 10 + 'A';
      }
      code2='\0';
      encodedString+='%';
      encodedString+=code0;
      encodedString+=code1;
      //encodedString+=code2;
    }
    yield();
  }
  return encodedString; 
}
