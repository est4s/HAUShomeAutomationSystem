// ESP8266 library
#include <ESP8266WiFi.h>

// EEPROM library
#include <EEPROM.h>

//------------------Firebase----------------
#include <FirebaseArduino.h>
#define FIREBASE_HOST "************************************"
#define FIREBASE_AUTH "************************************"

//------------------WiFi-------------------
#define WIFI_SSID "*********************"
#define WIFI_PASSWORD "****************"


//----------------dht11-------------------
#include "DHTesp.h"
#define DHTpin D5
DHTesp dht;

//--------------mq2 gaz sensor--------------
const int smokeA0= A0;

//-------------ultrasonic sensor-------------
const int trigPin = 2; //D4
const int echoPin = 16; //D0
long duration;
int distance;


//-------------------LEDS-------------------
const int led0= D1;
const int led1= D2;
const int led2= D6;

//-----------------INTERRUPT-----------------
uint8_t GPIO_Pin=D3;
void ICACHE_RAM_ATTR powerOff() {
    digitalWrite(led0, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    Serial.println("-----------------------Restarting-----------------------");
    Serial.println("Counting down: ");
    int j=6;
    for(int i=0;i<=6;i++){
      Serial.println(j);
      j--;
    delay(1000);
    digitalWrite(D8, HIGH);
      }
}



void setup() {
  
  Serial.begin(9600);
  
  //------------EEPROM------------
  EEPROM.begin(512);
  
  //------------INTERRUPT------------
  attachInterrupt(digitalPinToInterrupt(GPIO_Pin), powerOff, FALLING);

  //------------DHT11----------------
  dht.setup(DHTpin, DHTesp::DHT11);
  
  //---------mq2 gaz sensor----------
  pinMode(smokeA0, INPUT);
  
  //--------ultrasonic sensor---------
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //-------------LEDS----------------
  pinMode(led0, OUTPUT);digitalWrite(led0, LOW); 
  pinMode(led1, OUTPUT);digitalWrite(led1, LOW); 
  pinMode(led2, OUTPUT);digitalWrite(led2, LOW); 

//---------------relay--------------
  pinMode(D7, OUTPUT); digitalWrite(D7, HIGH);
  pinMode(D8, OUTPUT); digitalWrite(D8, LOW);
  
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

 //------------EEPROM---------------
 EEPROM.write(10, 231);
 Serial.println(EEPROM.read(10));

 //--Write EEPROM pass to Firebase--
 Firebase.setInt("EEPROMcode", EEPROM.read(10));
}

int x=1;

void loop() {
//----------------timer-------------------
unsigned long timer01= millis();
unsigned long desiredTime=x*300000;
  //-----------timer------------
  if(timer01>desiredTime){
    morningRoutine();
    x++;
    }
  Serial.println("--------------------------------");
    
    Serial.print("timer01: ");Serial.println(timer01);
  
  //LED0
  String ledStat0 = Firebase.getString("ledStat0");  
  Serial.print("Led Stat0: "); Serial.println(ledStat0);

  if(ledStat0=="1"){
    digitalWrite(led0, HIGH);
    }
  else if(ledStat0=="0"){
    digitalWrite(led0, LOW);
    }
    
  //LED1
  String ledStat1 = Firebase.getString("ledStat1");  
  Serial.print("Led Stat1: "); Serial.println(ledStat1);
  if(ledStat1=="1"){
    digitalWrite(led1, HIGH);
    }
  else if(ledStat1=="0"){
    digitalWrite(led1, LOW);
    }

  //LED2
  String ledStat3 = Firebase.getString("ledStat3");  
  Serial.print("Led Stat3: "); Serial.println(ledStat3);
  if(ledStat3=="1"){
    digitalWrite(led2, HIGH);
    }
  else if(ledStat3=="0"){
    digitalWrite(led2, LOW);
    }
    
  //-------ultrasonic sensor-------
  digitalWrite(trigPin, LOW); //clearing trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);//activating trigPin
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);//deactivating trigPin
  duration = pulseIn(echoPin,HIGH);//reading echoPin(travel time of soundwave)
  distance = duration*0.034/2;//calculating distance
  Serial.print("Distance: ");Serial.println(distance);

  if(distance<28){
    Firebase.setString("boxState", "1");
    if(Firebase.failed()){
      Serial.print("setting /boxState failed: ");
      Serial.println(Firebase.error());
    }
    }
   else{
    Firebase.setString("boxState", "0");
    if(Firebase.failed()){
      Serial.print("setting /boxState failed: ");
      Serial.println(Firebase.error());
    }
   }
  //----end of ultrasonic sensor program----

  //------------mq2 sensor------------
  int mq2 = analogRead(smokeA0);
  Serial.print("MQ2: ");Serial.println(mq2);
  if(mq2<350){
    Firebase.setString("mq2", "0");
    if(Firebase.failed()){
      Serial.print("setting /mq2 failed: ");
      Serial.println(Firebase.error());
    }
    }
   else{
    fireProcedure();
    Firebase.setString("mq2", "1");
    if(Firebase.failed()){
      Serial.print("setting /mq2 failed: ");
      Serial.println(Firebase.error());
    }
   }


   //-------------dht11----------------
  float temperature = dht.getTemperature();
  Serial.print("Temp: ");Serial.println(temperature);
    Firebase.setInt("temp", temperature);
    if(Firebase.failed()){
      Serial.print("setting /boxState failed: ");
      Serial.println(Firebase.error());
    }
  float humidity = dht.getHumidity();
  Serial.print("Hum: ");Serial.println(humidity);
    Firebase.setInt("hum", humidity);
    if(Firebase.failed()){
      Serial.print("setting /boxState failed: ");
      Serial.println(Firebase.error());
    }
  
}

void morningRoutine(){
  Serial.println("--------MORNING ROUTINE--------");
    digitalWrite(D7, LOW);
    digitalWrite(led0, HIGH);
    delay(3000);
    digitalWrite(led0, LOW);
    digitalWrite(led2, HIGH);
    delay(3000);
    digitalWrite(led2, LOW);
    digitalWrite(led1, HIGH);
    delay(3000);
    digitalWrite(D7, HIGH);
  }

void fireProcedure(){
  
    digitalWrite(D7, HIGH);
    digitalWrite(D8, HIGH);
    digitalWrite(led0, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    
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
