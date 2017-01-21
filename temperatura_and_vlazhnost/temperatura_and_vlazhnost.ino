#include "DHT.h"
#define DHTPIN 2 // номер пина, к которому подсоединен датчик
// Раскомментируйте в соответствии с используемым датчиком
// Инициируем датчик
//DHT dht(DHTPIN, DHT22);
DHT dht(DHTPIN, DHT11);
void setup() {
  Serial.begin(9600);
  dht.begin();
}
void loop() {
  // Задержка 2 секунды между измерениями
  delay(2000);
  //Считываем влажность
  float h = dht.readHumidity();
  // Считываем температуру
  float t = dht.readTemperature();
  // Проверка удачно прошло ли считывание.
  if (isnan(h) || isnan(t)) {
    Serial.println("Не удается считать показания");
    return;
  }

  //преобразовываем значения в строки

  double floatVal = h;
  char charVal[10];               //temporarily holds data from vals 
  String stringValH = "";     //data on buff is copied to this string
  
  dtostrf(floatVal, 3, 3, charVal);  //4 is mininum width, 4 is precision; float value is copied onto buff
  //display character array
  Serial.print("charVal: ");
  //for(int i=0;i<sizeof(charVal);i++)
  //{
  //  Serial.print(charVal[i]);
  //}
  //Serial.println();
  //convert chararray to string
  for(int i=0;i<sizeof(charVal);i++)
  {
    stringValH+=charVal[i];
  }

  double floatValT = t;
  char charValT[10];  
  String stringValT = "";     //data on buff is copied to this string
  dtostrf(floatValT, 3, 3, charValT);  //4 is mininum width, 4 is precision; float value is copied onto buff
  for(int i=0;i<sizeof(charValT);i++)
  {
    stringValT+=charValT[i];
  }
  
  Serial.println("Humidity: " + stringValH + " %\t" + "Temperature: " + stringValT + " *C ");
}
