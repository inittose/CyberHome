#include <TroykaCurrent.h> 
 
ACS712 sensorCurrent(A18); 
 
void setup() { 
  Serial.begin(9600); 
  Wire.begin(); 
  
 
  current_I_cal = sensorCurrent.readCurrentDC(); 
  delay(1000); 
} 
 
void loop() { 
  Serial.print(sensorCurrent.readCurrentDC() - current_I_cal); 
  Serial.println(" A"); 
   
  delay(10); 
}
