#include "Callmebot.h"

const String BASE_URL = "http://api.callmebot.com/whatsapp.php";

String generate_url(String msg) {
  String url = BASE_URL;
  url = url + "?phone=" + CMB_PHONE;
  url = url + "&text=" + url_encode(msg);
  url = url + "&apikey=" + CMB_TOKEN;

  return url;
}

String url_encode(String str)
{
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

String send_message(String msg) {
  Serial.println("Sending message to whatsapp");

  WiFiClient client;
  HTTPClient http;

  http.begin(client, generate_url(msg));

  int httpCode = http.GET();

  if (httpCode < 0) {
    Serial.println("Callmebot request error - " + httpCode);
    return "";
  }

  String response = http.getString();

  http.end();

  return response;
}