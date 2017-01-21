// Реле модуль подключен к цифровому выводу 4
int Relay = 2;

void setup() 
{                
    pinMode(Relay, OUTPUT);     
    pinMode(13, OUTPUT);
}

void loop() 
{
  
  digitalWrite(Relay, HIGH);  // реле выключено
  digitalWrite(13, LOW);   // реле включено
  delay(2000);   


 
  digitalWrite(Relay, LOW);   // реле включено
  digitalWrite(13, HIGH);   // реле включено
  delay(2000);               




}
