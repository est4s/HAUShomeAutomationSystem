// ESP8266 library
#include <ESP8266WiFi.h>

// EEPROM library
#include <EEPROM.h>

//------------------Firebase----------------
#include <FirebaseArduino.h>
#define FIREBASE_HOST "***************************************"
#define FIREBASE_AUTH "***************************************"

//------------------WiFi-------------------
#define WIFI_SSID "***********************"
#define WIFI_PASSWORD "*******************"

//GPIO setup
//const int relay0= D0;
const int relay1= D1;


float vref = 3.3;
float resolution = vref/1023;






//-------------------pump------------------
const int pumpPin= D0;
int countPump=0;


void setup() {

  Serial.begin(9600);






  //-------------pump-----------------
  pinMode(pumpPin, OUTPUT); digitalWrite(pumpPin, HIGH);
  //--------------relays--------------
  //pinMode(relay0,OUTPUT);digitalWrite(relay0, HIGH);
  pinMode(relay1,OUTPUT);digitalWrite(relay1, LOW);

  //--------------lm35----------------
  //pinMode(lm35,INPUT);
  
  //----------wifi connection--------
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();

  //----------Firebase-----------------
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {
 
  String powerStat = Firebase.getString("power");  
  Serial.print("power: "); Serial.println(powerStat);
  
  if(powerStat=="1"){
    digitalWrite(relay1, LOW);
    delay(100);
    interruptSend();
    }
  else if(powerStat=="0"){
    digitalWrite(relay1, HIGH);
    }

  //------pump program------
  String pump = Firebase.getString("pump");  
  Serial.print("Pump: "); Serial.println(pump);

  if(pump=="1"){
    digitalWrite(pumpPin, LOW);
    countPump++;
    pump=2;
    }
    
  if(countPump>0 && countPump<6){
    countPump++;
    }
  else if(countPump>=3){
    countPump=0;
    digitalWrite(pumpPin, HIGH);
    Firebase.setString("pump", "0");
    if(Firebase.failed()){
      Serial.print("setting /pump failed: ");
      Serial.println(Firebase.error());
    }
  }
  Serial.print("Pump counter: ");Serial.println(countPump);
  delay(200);
  //------end of pump program------


}

void interruptSend(){

    Firebase.setString("power", "0");
    if(Firebase.failed()){
      Serial.print("setting /power failed: ");
      Serial.println(Firebase.error());
    }
  
    Firebase.setString("ledStat0", "0");
    if(Firebase.failed()){
      Serial.print("setting /ledStat0 failed: ");
      Serial.println(Firebase.error());
    }
    Firebase.setString("ledStat1", "0");
    if(Firebase.failed()){
      Serial.print("setting /ledStat1 failed: ");
      Serial.println(Firebase.error());
    }
    Firebase.setString("ledStat2", "0");
    if(Firebase.failed()){
      Serial.print("setting /ledStat2 failed: ");
      Serial.println(Firebase.error());
    }
    Firebase.setString("ledStat3", "0");
    if(Firebase.failed()){
      Serial.print("setting /ledStat3 failed: ");
      Serial.println(Firebase.error());
    }
    Firebase.setString("pump", "0");
    if(Firebase.failed()){
      Serial.print("setting /pump failed: ");
      Serial.println(Firebase.error());
    }
    
    
  
  }
