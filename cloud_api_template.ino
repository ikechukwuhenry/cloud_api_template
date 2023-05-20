// ST_7789_240x240TFT_most simple
// Floris Wouterlood 20 December 2019
// public domain
// sketch for NodeMCU ESP8266 
// displays HELLO WORLD on a 1.3 inch 3.3V TFT_display with ST7789 controller 
// 240 x 240 pixels in this confguration
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClientSecureBearSSL.h>
// Fingerprint for demo URL, expires on June 2, 2021, needs to be updated well before this date
//const uint8_t fingerprint[20] = {0x40, 0xaf, 0x00, 0x6b, 0xec, 0x90, 0x22,
//0x41, 0x8e, 0xa3, 0xad, 0xfa, 0x1a, 0xe8, 0x25, 0x41, 0x1d, 0x1a, 0x54, 0xb3};

ESP8266WiFiMulti WiFiMulti;

String secureUrl;
String secureUrl2;
String secureUrl3;
String secureUrl4;
int left = 0;
int right = 0;
int total = 0;
String user = "";

//{
//  "deviceId": "3as330",
//  "temperature": 30,
//  "smoke": 99,
//  "co": 30,
//  "humidity": 84,
//  "lpg": 30,
//  "latitude": 380,
//  "longitude": 80
//}
//  
 
 void setup(void) { 
   Serial.begin (9600);
 
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Multiverse", "praiseGod");
  user = WiFi.macAddress();
  delay(3000); 
 }

 void loop (){
    // Channel 0 (C0 pin - binary output 0,0,0,0)
  String deviceId = "3as330";
  float temp = 30;
  float smokes = 99;
  float coxide = 30;
  float humid = 84;
  float lpgs = 30;
  float lat = 380;
  float longitudes = 80;
    
    if ((WiFiMulti.run() == WL_CONNECTED)) {
//    int maxMicData = 0;
//    for(int i = 0; i < 10000; ++i) {
//      int sensorValue = 123; //analogRead(A0);
//      maxMicData = max(maxMicData, sensorValue);
//      delayMicroseconds(100);
//      yield();
//    }
    Serial.println("uploading data");
    fireUrl2(deviceId, temp, smokes, coxide, humid, lpgs, lat, longitudes);
  }
  Serial.println("Wait 1s before next round...");
  delay(1000);
 }

 void fireUrl(int data, int left, int right, int total) {
//  secureUrl = String("https://hook.integromat.com/fmonn33rqamis2ihg1qizw330c421ibh?mic=") + data;
    String left2 = String(left);    //  random(0, 70);
    String right2 = String(right);     //  random(0, 70);
    String total2 = String(total);    // random(0, 140);
//  secureUrl = String("https://hook.integromat.com/9gds6tdsw1gl4dt7lb5ug1a4esgnnirw?left=30&right=74&total=108");

  
 secureUrl = String("https://hook.integromat.com/9gds6tdsw1gl4dt7lb5ug1a4esgnnirw?left=") + left + "&right=" + right + "&total=" + total;

 secureUrl4 = String("https://sonvisage-backend.herokuapp.com/project/health/?left=") + left2 + "&right=" + right2 + "&total=" + total2 + "&user_id=" + user +"&date=2022-06-03";

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  // client->setFingerprint(fingerprint);
  // Or, if you happy to ignore the SSL certificate, then use the following line instead:
  client->setInsecure();
  HTTPClient https;
  Serial.print("[HTTPS] begin...\n");
  if (https.begin(*client, secureUrl4)) {  // HTTPS
    int httpCode = https.GET();
    if (httpCode > 0) {
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        Serial.println(payload);
      }
    }
    else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
  }
  else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }
}

 void fireUrl2(String deviceId, float temp, float smokes, float coxide, float humid, float lpgs, float lat, float longitudes) {
//  secureUrl = String("https://hook.integromat.com/fmonn33rqamis2ihg1qizw330c421ibh?mic=") + data;
    String temperature = String(temp);    
    String smoke = String(smokes);    
    String co = String(coxide);    
    String humidity = String(humid);    
    String lpg = String(lpgs);    
    String latitude = String(lat); 
    String longitude = String(longitudes); 


 secureUrl4 = String("https://gas-sensor.onrender.com/api-docs/#/Misc/createsensordata/?deviceId=") + deviceId + "&temperature=" + temperature + "&smoke=" + smoke + "&co=" + co +"&humidity" + humidity + "&lpg=" + lpg + "&latitude=" + latitude + "&longitude=" + longitude;

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  // client->setFingerprint(fingerprint);
  // Or, if you happy to ignore the SSL certificate, then use the following line instead:
  client->setInsecure();
  HTTPClient https;
  Serial.print("[HTTPS] begin...\n");
  if (https.begin(*client, secureUrl4)) {  // HTTPS
    int httpCode = https.GET();
    if (httpCode > 0) {
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        Serial.println(payload);
      }
    }
    else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
  }
  else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }
}
