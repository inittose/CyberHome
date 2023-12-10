#include <PCA9536.h> 
#include <Wire.h> 
PCA9536 pca9536;  
 
uint8_t  pinSensor = 2;                                         // Определяем номер вывода Arduino, к которому подключён датчик расхода воды. 
byte incomingByte; 
uint32_t varTime = 0;                                               // Объявляем переменную для хранения времени последнего расчёта. 
float    varQ = 0;                                                  // Объявляем переменную для хранения рассчитанной скорости потока воды (л/с). 
float    varV = 0;                                                  // Объявляем переменную для хранения рассчитанного объема воды (л). 
volatile uint16_t varF = 0;                                         // Объявляем переменную для хранения частоты импульсов (Гц). 
                                                                // 
void funCountInt(){varF++;}                                     // Определяем функцию, которая будет приращать частоту импульсов. 
                                                                // 
void setup(){                                                   // 
     Serial.begin(9600);                                        // Инициируем передачу данных в монитор последовательного порта. 
     Wire.begin();  
     pca9536.reset();  
  pca9536.setMode(IO_OUTPUT);  
     pinMode(pinSensor, INPUT);                                 // Конфигурируем вывод к которому подключён датчик, как вход. 
     uint8_t intSensor = digitalPinToInterrupt(pinSensor);      // Определяем номер прерывания который использует вывод pinSensor. 
     attachInterrupt(intSensor, funCountInt, RISING);           // Назначаем функцию funCountInt как обработчик прерываний intSensor при каждом выполнении условия RISING - переход от 0 к 1. 
     if(intSensor<0){Serial.print("Указан вывод без EXT INT");} // Выводим сообщение о том, что датчик подключён к выводу не поддерживающему внешнее прерывание. 
    // varTime=0; varQ=0; varV=0; varF=0;                       // Обнуляем все переменные. 
}                                                               // 
                                                                // 
void loop(){                                                    // 
//   Если прошла 1 секунда:              
    if (Serial.available() > 0) { 
    incomingByte = Serial.read(); 
    if(incomingByte == '1'){ 
      //digitalWrite(ledPin, HIGH); 
      pca9536.setState(IO1, IO_HIGH); 
      Serial.println("on"); 
    } 
    else if (incomingByte == '0'){ 
      //digitalWrite(ledPin, LOW); 
      pca9536.setState(IO1, IO_LOW);  
      Serial.println("off"); 
    } 
     
     if( (varTime+1000)<millis() || varTime>millis() ){         // Если c момента последнего расчёта прошла 1 секунда, или произошло переполнение millis то ... 
     //  Определяем скорость и расход воды:                     // 
         varQ    = (float)varF / 450.0f;                        // Определяем скорость потока воды л/с. 
         varF    = 0;                                           // Сбрасываем частоту импульсов датчика, значение этой переменной приращается по прерываниям. 
         varTime = millis();                                    // Сохраняем  время последних вычислений. 
         varV   += varQ;                                        // Определяем объем воды л. 
     //  Выводим рассчитанные данные:                           // 
         Serial.println((String) "Объем "+varV+"л, скорость "+(varQ*60.0f)+"л/м."); 
     }                                                          // 
//   Тут может выполняться ваш код ...                          // 
}    }
