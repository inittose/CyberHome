#include <BH1750.h> 
#include <Wire.h> 
BH1750 lightMeter; 
 
void setup() { 
  Serial.begin(9600); 
  Wire.begin(); 
  lightMeter.begin(); 
  //ledcSetup(23, 200, 8);  
  //ledcAttachPin(23, 0); 
  pinMode(5, OUTPUT); 
  Serial.println(F("BH1750 Test begin")); 
} 
 
void loop() { 
  float lux = lightMeter.readLightLevel(); 
  int light = (map(lux, 0, 300, 256, 0)); 
  light = constrain(light, 0, 256); 
  analogWrite(5, light); 
  Serial.println(light); 
   
  delay(10); 
}
