#include <Adafruit_GFX.h> // Core graphics library
#include <Fonts/FreeSans9pt7b.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include <SSD1306.h> // alias for `#include "SSD1306Wire.h"`
SSD1306  display(0x3c, 5, 4); // Initialize the OLED display using Wire library
#include <MQ135.h>
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

/* DHT22 */
#include <DHT.h>
#define DHTPIN D3  
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);
int localHum = 0;
int localTemp = 0;
/* MQ135 */
int mq135Pin = A0;
int sensorValue;
float air_quality;
/* ultrasonic Sensor */
#define trigPin D8
#define echoPin D7
#define led1 D0
#define led2 D4
#define led3 D5
#define led4 D6
long duration;
int distance;
long count;
boolean flag=true;
char ssid[] = "ICE_Innovation_Lab";
char wifiPassword[] = "bolajabena15";
char username[] = "6d9b9800-c3c4-11e8-9747-bb363659b178";
char password[] = "860d76e70b2b9f9502cb41568129a1ff99416a2e";
char clientID[] = "b1123490-c586-11e8-b13e-3759b595b70c";
void setup() 
{
  Serial.begin(115200);
  display.init(); // Initialising the UI will init the display too.
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  display.flipScreenVertically();
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() 
{
  Cayenne.loop();
  getDHT();
  getAirQuality();
  getDistance();
  led();
  display.clear();
  drawDHT(); 
  drawDistance();
  display.display();
  delay (1000);
}

/***************************************************
* Get indoor Temp/Hum data
****************************************************/
void getDHT()
{
  float tempIni = localTemp;
  float humIni = localHum;
  localTemp = dht.readTemperature();
  localHum = dht.readHumidity();
  if (isnan(localHum) || isnan(localTemp))   // Check if any reads failed and exit early (to try again).
  {
    Serial.println("Failed to read from DHT sensor!");
    localTemp = tempIni;
    localHum = humIni;
    return;
  }
}
/***************************************************
* Get Co2 from MQ135
****************************************************/
void getAirQuality(){
  MQ135 gasSensor = MQ135(A0);
  air_quality = gasSensor.getPPM();
  Serial.print("Air quality: ");
  Serial.print(air_quality);
  Serial.println("ppm");
  if (air_quality<=1000)
  {
    Serial.println("Fresh Air");
  }
  else if( air_quality>=1000 && air_quality<=2000 )
  {
    Serial.println("Poor Air, Open Windows");
    //displayPoor();
  }
  else if (air_quality>=2000 )
  {
    Serial.println("Danger! Move to Fresh Air");
    //displayDanger();
    
  }
}
void getDistance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
}

/***************************************************
* Draw Indoor Page
****************************************************/
void drawDHT() 
{
  int x=0;
  int y=0;
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0 + x, 5 + y, "Hum");
  
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(43 + x, y, "INDOOR");

  display.setFont(ArialMT_Plain_16);
  String hum = String(localHum) + "%";
  display.drawString(0 + x, 15 + y, hum);
  int humWidth = display.getStringWidth(hum);

  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(95 + x, 5 + y, "Temp");

  display.setFont(ArialMT_Plain_16);
  String temp = String(localTemp) + "°C";
  display.drawString(80 + x, 15 + y, temp);
  int tempWidth = display.getStringWidth(temp);

  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0 + x, 30 + y, "Air Quality");

  
  display.setFont(ArialMT_Plain_16);
  String ppm = String(air_quality) + "ppm";
  display.drawString(0 + x, 40 + y, ppm);
  int ppmWidth = display.getStringWidth(ppm);
  
}

/***************************************************
* Draw Distance level
****************************************************/
void drawDistance(){
  int x=0,y=0;
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(85 + x, 30 + y, "Distance");
  
  display.setFont(ArialMT_Plain_10);
  String temp = String(distance) + "cm";
  display.drawString(85 + x, 40 + y, temp);
  int tempWidth = display.getStringWidth(temp);
  
}
void led(){
  if((distance>=5)&&(distance<=12)){
    digitalWrite(led1,HIGH);
    delay(1000);
    digitalWrite(led2,HIGH);
    delay(1000);
    digitalWrite(led3,HIGH);
    delay(1000);
    digitalWrite(led4,HIGH);  
    count++;
    if(count%2==0){
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
     }
  }
  else{
    CAYENNE_IN(1);
    CAYENNE_IN(2);
    CAYENNE_IN(3);
    CAYENNE_IN(4);
    
  }
  
  Serial.print("counter: ");
  Serial.println(count);
}

CAYENNE_OUT_DEFAULT()
  {
    Cayenne.virtualWrite(5,localTemp);
    Cayenne.virtualWrite(6,localHum);
    Cayenne.virtualWrite(7,air_quality);
  }
CAYENNE_IN(1)  // button
  {   
    int currentValue=getValue.asInt();
    
     if(currentValue==1)
     {
       digitalWrite(led1,HIGH);
     }
     else
     {
       digitalWrite(led1,LOW); 
     }
  }
CAYENNE_IN(2)  // button
  {   
    int currentValue=getValue.asInt();
    
     if(currentValue==1)
     {
       digitalWrite(led2,HIGH);
     }
     else
     {
       digitalWrite(led2,LOW); 
     }
  }
CAYENNE_IN(3)  // button
  {   
    int currentValue=getValue.asInt();
    
     if(currentValue==1)
     {
       digitalWrite(led3,HIGH);
     }
     else
     {
       digitalWrite(led3,LOW); 
     }
  }
CAYENNE_IN(4)  // button
  {   
    int currentValue=getValue.asInt();
    
     if(currentValue==1)
     {
       digitalWrite(led4,HIGH);
     }
     else
     {
       digitalWrite(led4,LOW); 
     }
  }

