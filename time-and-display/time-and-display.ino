// Бибилиотека разработана для RTC модуля http://iarduino.ru/shop/Expansion-payments/chasy-realnogo-vremeni-rtc-trema-modul.html

#include <iarduino_RTC.h>
#include <LiquidCrystal.h>

//iarduino_RTC ОБЪЕКТ ( НАЗВАНИЕ [, ВЫВОД_RST [, ВЫВОД_CLK [, ВЫВОД_DAT ]]] ); // Создаём объект. 
iarduino_RTC time(RTC_DS1302,10,12,11);

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, DB4, DB5, DB6, DB7)

void setup() {
  lcd.begin(16, 2);                     // Задаем размерность экрана

  delay(300);
  Serial.begin(9600);
  time.begin();
  // 0  сек, 36 мин, 21 час, 27, октября, 2015 года, вторник
  // time.settime(0, 40, 8, 4, 2, 18, 7);    
}
void loop(){
  String fullTime = time.gettime("d-m-Y, H:i:s, D");  
  Serial.print(fullTime);

  String dateString = time.gettime("d-m-Y");
  String timeString = time.gettime("H:i:s");
   
  showDateTimeToDisplay(dateString, timeString);
   
  delay(1000); 
}

void showDateTimeToDisplay(String dateString, String timeString){
  lcd.setCursor(0, 0);                // Устанавливаем курсор в начало 1 строки
  lcd.print("date: " + dateString);   // Выводим текст
  lcd.setCursor(0, 1);                // Устанавливаем курсор в начало 2 строки
  lcd.print("time: " + timeString);   // Выводим текст
}

