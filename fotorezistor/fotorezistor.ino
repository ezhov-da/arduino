/* Простой проверочный скетч для фоторерезистора.
Подключите одну ногу фоторезистора к 5 В, вторую к пину Analog 0.
После этого подключите контакт резистора на 10 кОм к земле, а второй к аналоговому пину Analog 0 */
int photocellPin = 0; // сенсор и понижающий резистор на 10 кОм подключены к a0
int photocellReading; // данные считываемые с аналогового пина
void setup(void) {
  // Передаем информацию для дебагинга на серийный монитор
  Serial.begin(9600);
}
void loop(void) {
  photocellReading = analogRead(photocellPin);
  Serial.print("Analog reading = ");
   Serial.print(photocellReading); // аналоговые значения
  if (photocellReading < 10) {
    Serial.println(" - Dark");
  } else if (photocellReading < 200) {
    Serial.println(" - Dim");
  } else if (photocellReading < 500) {
    Serial.println(" - Light");
  } else if (photocellReading < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
    delay(1000);
}
