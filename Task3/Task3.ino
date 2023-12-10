unsigned long timerr = 0; 
unsigned long led_timer = 0; 
bool led_state = 0; 
#include <ESP32Servo.h> 
Servo door; 
Servo window; 
 
#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30 
#include <Wire.h> 
#include "PCA9536.h" 
PCA9536 pca9536; 
SGP30 mySensor; //create an object of the SGP30 class 
 
 
void setup() {  
  door.attach(14); 
   window.attach(15); 
   pinMode(5, OUTPUT);  
  // put your setup code here, to run once: 
  Serial.begin(9600); 
  Wire.begin(); 
  pca9536.reset(); 
  pca9536.setMode(IO_OUTPUT); 
  //Initialize sensor 
  if (mySensor.begin() == false) { 
    Serial.println("No SGP30 Detected. Check connections."); 
    while (1); 
  } 
  //Initializes sensor for air quality readings 
  //measureAirQuality should be called in one second increments after a call to initAirQuality 
  mySensor.initAirQuality(); 
} 
 
void loop() { 
  // put your main code here, to run repeatedly: 
if(millis() - timerr > 1000) { 
 mySensor.measureAirQuality(); 
  Serial.print("CO2: "); 
  Serial.println(mySensor.CO2); 
 
  if(mySensor.CO2 > 550) { 
     pca9536.setState(IO0, IO_HIGH); 
     door.write(0); 
     window.write(180); 
        if(millis() - led_timer > 1000) { 
        led_state = !led_state; 
        digitalWrite(5, led_state); 
        led_timer = millis(); 
          } 
 
    } else { 
      pca9536.setState(IO0, IO_LOW); 
     door.write(180); 
     window.write(0); 
     digitalWrite(5, 0); 
     led_timer = millis(); 
    } 
  timerr = millis(); 
} 
} 