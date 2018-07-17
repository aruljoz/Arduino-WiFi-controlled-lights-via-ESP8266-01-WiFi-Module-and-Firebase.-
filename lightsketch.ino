//The ESP8266WiFi.h library is included to inherit pre-defined functions of ESP-01 wifi module.
//The Firebase library is used to link to the cloud for online control.
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

//The WiFi credentials are defined here.
#define WIFI_SSID "Umande"
#define WIFI_PASSWORD "@mukima-2020"

//connecting to the Firebase server. The database secret key and project URL is used.
#define FIREBASE_HOST "lightscontrol-808.firebaseio.com"
#define FIREBASE_AUTH "qi2UoXbB0HSoNm9TXdMoxoZbVvhlBd0C3u05UXYH"

//ESP-01 pin to be used for signal transmission
int triggerPin = 2;




void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);//baud rate for serial communication through Arduino board
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Control to check if the WiFi is connected
  Serial.print("Authenticating Credentials");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500); //If the connection is not yet established, print a dot every half a second
    }
    Serial.println();//Enables the subsequent characters to be printed in human-readable ASCII text
    Serial.println("Connection Established");
    Serial.println(WiFi.localIP());//Display the IP address.

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //Initialize firebase for the program.
    pinMode(triggerPin, OUTPUT); //set GPIO2 Pin as the signal generator to trigger bulb state. 
}

void loop() {
  // put your main code here, to run repeatedly:
  int lightState = Firebase.getInt("lightState");
  Serial.println(lightState); //set baud to 9600 in serial monitor since arduino fastest communication speed is 9600

  //control code to turn on the lights when the Firebase server's signal is a 0 and turn the light off when it's a 1
  //reverse is used because the relay to trigger the lights is a PNP configuration.
  if (lightState == 0){
      digitalWrite(triggerPin, HIGH);
      }
      else{
        digitalWrite(triggerPin, LOW);
        }

}
