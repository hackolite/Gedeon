#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>   // Include the WebServer library
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial
ESP8266WiFiMulti wifiMulti;
#include <ArduinoJson.h>


int sensorData = 0 ;

void setup(void){
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("", "");   // add Wi-Fi networks you want to connect to
  //wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  //wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
}

void loop(void){
        HTTPClient http;
        StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
        JsonObject& JSONencoder = JSONbuffer.createObject(); 
 
        JSONencoder["sensorType"] = "H2s";
        sensorData = analogRead(A0);
        JsonArray& values = JSONencoder.createNestedArray("values"); //JSON array
        values.add(sensorData); //Add value to array
 
        JsonArray& timestamps = JSONencoder.createNestedArray("latitude"); //JSON array
        timestamps.add("10"); //Add value to array
        
        JsonArray& timestamps2 = JSONencoder.createNestedArray("longitude"); //JSON array
        timestamps2.add("10000"); //Add value to array

        JsonArray& timestamps3 = JSONencoder.createNestedArray("id"); //JSON array
        timestamps3.add("1810"); //Add value to array


        JsonArray& timestamps4 = JSONencoder.createNestedArray("token"); //JSON array
        timestamps4.add("1804"); //Add value to array

        char JSONmessageBuffer[300];
        JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
        Serial.println(JSONmessageBuffer);

        
        http.begin("http://213.246.57.145:5000/pollution"); //HTTP
        int httpCode = http.POST(JSONmessageBuffer);
        
        // start connection and send HTTP header
        //sensorData = analogRead(A0);
        //String myString = String(sensorData);
        // int httpCode = http.POST(myString);
        delay(1000);                    // Listen for HTTP requests from clients
}
