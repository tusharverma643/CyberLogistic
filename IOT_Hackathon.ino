#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
String readString;
const char* ssid = "Akshit";
const char* password = "lollol123";
const char* host = "script.google.com";
const int httpsPort = 443;
WiFiClientSecure client;
const char* fingerprint = "46 B2 C3 44 9C 59 09 8B 01 B6 F8 BD 4C FB 00 74 91 2F EF F6";
String GAS_ID = "AKfycbxmJhC2ceAWaEGg6VEvAbZ-iRYbNOyChTGqQaTZ5FY-";  
void setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }       
    sendData("123","Chandigarh","30.9084 N", "77.0999 E","In Transit"); 
    delay(1000);
    sendData("111","New Delhi","28.9931 N", "77.0151 E","In Transit"); 
    delay(1000);  
    sendData("123","Chandigarh","30.8406 N","76.9584 E","In Transit"); 
    delay(1000); 
     
}
void loop()
{

}
void sendData(String x, String y, String z, String t, String r)
{
 client.setInsecure();
 Serial.print("connecting to ");
 Serial.println(host);
 if (!client.connect(host, httpsPort))
 {
   Serial.println("connection failed");
   return;
 }
 if (client.verify(fingerprint, host))
 {
 Serial.println("certificate matches");
 } 
 else 
{
 Serial.println("certificate doesn't match");
 }
 String string_x     =  x;
 String string_y     =  y;
 String string_z     =  z;
 String string_t     =  t;
 String string_r     =  r;
 String url = "/macros/s/" + GAS_ID + "/exec?out1=" + string_x + "&out2=" + string_y + "&out3=" + string_z + "&out4=" + string_t + "&out5=" + string_r;
 Serial.print("requesting URL: ");
 Serial.println(url);
 client.print(String("GET ") + url + " HTTP/1.1\r\n" +
        "Host: " + host + "\r\n" +
        "User-Agent: BuildFailureDetectorESP8266\r\n" +
        "Connection: close\r\n\r\n");
 Serial.println("request sent");
 while (client.connected()) {
 String line = client.readStringUntil('\n');
 if (line == "\r") {
   Serial.println("headers received");
   break;
 }
 }
 String line = client.readStringUntil('\n');
 if (line.startsWith("{\"state\":\"success\"")) {
 Serial.println("esp8266/Arduino CI successfull!");
 } else {
 Serial.println("esp8266/Arduino CI has failed");
 }
 Serial.println("reply was:");
 Serial.println("==========");
 Serial.println(line);
 Serial.println("==========");
 Serial.println("closing connection");
}
