#include <CayenneMQTTESP32.h>
#define CAYENNE_PRINT Serial
#define LDR_4 36 //vp pin esp32
#define LDR_2 39 //un pi esp32

int ldrValue_1,ldrValue_2,ldrValue_3,ldrValue_4;
int actualValueLdr_1,actualValueLdr_2,actualValueLdr_3,actualValueLdr_4;
char ssid[] = "ICE_Innovation_Lab";
char wifiPassword[] = "bolajabena15";
char username[] = "6d9b9800-c3c4-11e8-9747-bb363659b178";
char password[] = "860d76e70b2b9f9502cb41568129a1ff99416a2e";
char clientID[] = "9372c370-c6f1-11e8-9ed6-8be9a65b057d"; 
 
int flag1,flag2,flag3,flag4;

void setup(){
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(LDR_2,INPUT);
  pinMode(LDR_4,INPUT);
  Serial.begin(115200);
}
void loop()
{
  Cayenne.loop();
  ldrValue_1=analogRead(33);//light 1
  
  ldrValue_2=analogRead(LDR_4);//light 2
  ldrValue_3=analogRead(35);//light 3
  ldrValue_4=analogRead(LDR_2);//light 4
  
  actualValueLdr_1=ldrValue_1/10;
  actualValueLdr_2=ldrValue_2/10;
  actualValueLdr_3=ldrValue_3/10;
  actualValueLdr_4=ldrValue_4/10;
  
  Serial.print("The value of LDR_1 is: ");
  Serial.println(flag1);
  Serial.print("The value of LDR_2 is: ");
  Serial.println(flag2);
  Serial.print("The value of LDR_3 is: ");
  Serial.println(flag3);
  Serial.print("The value of LDR_4 is: ");
  Serial.println(flag4);
  if(actualValueLdr_1>=400){
    flag1=1;
  }
  if(actualValueLdr_1<400){
    flag1=0;
  }
  if(actualValueLdr_2>=270){
    flag2=1;
  }
  if(actualValueLdr_2<270){
    flag2=0;
  }
  if(actualValueLdr_3>=400){
    flag3=1;
  }
  if(actualValueLdr_3<400){
    flag3=0;
  }
  if(actualValueLdr_4>=400){
    flag4=1;
  }
  if(actualValueLdr_4<400){
    flag4=0;
  }
  delay(1000);
}
CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  Cayenne.virtualWrite(0,flag1);
  Cayenne.virtualWrite(1, flag2);
  Cayenne.virtualWrite(2, flag3);
  Cayenne.virtualWrite(3, flag4);
}

