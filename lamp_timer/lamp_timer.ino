// Бибилиотека разработана для RTC модуля http://iarduino.ru/shop/Expansion-payments/chasy-realnogo-vremeni-rtc-trema-modul.html

#include <iarduino_RTC.h>
iarduino_RTC time(RTC_DS1302,10,12,11);

// Реле модуль подключен к цифровому выводу 4
int relay = 2;
const int HOUR_ON_LAMP = 10;
const int HOUR_OFF_LAMP = 21;

void setup() {
    delay(300);
    Serial.begin(9600);
    time.begin();
    // 0  сек, 51 мин, 21 час, 27, октября, 2015 года, вторник
    //time.settime(0,36,21,21,1,17,6); 

    pinMode(relay, OUTPUT);     
    pinMode(13, OUTPUT);    
}
void loop(){
    Serial.println(time.gettime("d-m-Y, H:i:s, D"));
    String hour = time.gettime("H");
    int hourInt = hour.toInt();
    //если часы между с и по и реле выключено, тогда включаем его
    if (hourInt >= HOUR_ON_LAMP & hourInt < HOUR_OFF_LAMP){
      digitalWrite(relay, LOW);
      Serial.print(hour);
      Serial.println(" - rele is ON");
    //если часы меньше с  или больше по и реле включено, тогда выключаем
    } else if (hourInt < HOUR_ON_LAMP | hourInt >= HOUR_OFF_LAMP){
      digitalWrite(relay, HIGH);
      Serial.print(hour);
      Serial.println(" - rele is OFF");
    }
   delay(60000); 
}
