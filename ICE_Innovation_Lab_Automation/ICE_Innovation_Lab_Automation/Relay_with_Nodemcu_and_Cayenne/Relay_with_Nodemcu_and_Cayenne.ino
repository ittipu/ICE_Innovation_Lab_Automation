#define led_1 D0
#define led_2 D4
#define led_3 D5
#define led_4 D6
#define dhtPin D4
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <DHT.h>
DHT dht(dhtPin, DHT22);
char ssid[] = "ICE_Innovation_Lab";
char wifiPassword[] = "bolajabena15";
char username[] = "6d9b9800-c3c4-11e8-9747-bb363659b178";
char password[] = "860d76e70b2b9f9502cb41568129a1ff99416a2e";
char clientID[] = "b2746920-c3c4-11e8-9d14-ad5aab7fa45b";
float temp, hum;
void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  dht.begin();
}
void loop() {
  Cayenne.loop();
  temp=dht.readTemperature();
  hum=dht.readHumidity();
  delay(1000);
}
CAYENNE_OUT_DEFAULT()
{
  Cayenne.virtualWrite(5,temp);
  Cayenne.virtualWrite(6,hum);
}
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());

  if (request.channel = 1)
  {
    int currentValue=getValue.asInt();
  
   if(currentValue==1)
   {
     digitalWrite(led_1,HIGH);
   }
   else
   {
     digitalWrite(led_1,LOW); 
   }
  }
  else if (request.channel = 2)
  {
    int currentValue=getValue.asInt();
  
   if(currentValue==1)
   {
     digitalWrite(led_2,HIGH);
   }
   else
   {
     digitalWrite(led_2,LOW); 
   }
  }
  else if (request.channel = 3)
  {
    int currentValue=getValue.asInt();
  
   if(currentValue==1)
   {
     digitalWrite(led_3,HIGH);
   }
   else
   {
     digitalWrite(led_3,LOW); 
   }
  }
  else if (request.channel = 4)
  {
    int currentValue=getValue.asInt();
  
   if(currentValue==1)
   {
     digitalWrite(led_4,HIGH);
   }
   else
   {
     digitalWrite(led_4,LOW); 
   }
  }
}


