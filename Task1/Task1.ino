#include <Wire.h> 
#include <Adafruit_Sensor.h> 
#include <Adafruit_BME280.h> 
#include <ESP32Servo.h> 
Servo window; 
Adafruit_BME280 bme280; 
unsigned long TempTimer = 0; 
float angle = 0; 
void setup() { 
  // Инициализация последовательного порта 
  Serial.begin(9600); 
  window.attach(15); 
  // Инициализация датчика 
  bool bme_status = bme280.begin(); 
  if (!bme_status) 
    Serial.println("Could not find a valid BME280 sensor, check wiring!"); 
   
} 
 
void loop() { 
  // Измерение 
  if(millis()-TempTimer>250){ 
  float t = bme280.readTemperature(); 
  // Вывод измеренных значений в терминал 
  Serial.println("Air temperature = " + String(t, 1) + " *C, angle =" +String(angle, 1)); 
  angle = map(t*1000, 23000, 29000, 0, 160); 
  TempTimer = millis(); 
  window.write(angle); 
  } 
}
