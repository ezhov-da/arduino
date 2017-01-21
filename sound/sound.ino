long soundTime = 0; // время 1-го хлопка
int soundinputPin = 2;               // choose the input pin (for PIR sensor)
int releOutputPin = 8;
int soundState = LOW;             // we start, assuming no motion detected
int soundval = 0;                    // variable for reading the pin status

boolean start = false;


void setup() {

  pinMode(soundinputPin, INPUT);     // declare sensor as input
  pinMode(13, OUTPUT);     // declare sensor as input
  pinMode(releOutputPin, OUTPUT);     // declare sensor as input
  Serial.begin(9600);
}

void loop() {
  soundval = digitalRead(soundinputPin);  // read input value
  if (soundval == HIGH) {            // check if the input is HIGH
    if (soundState == LOW) {
      // we have just turned on
      long secondSoundTime = millis(); // лучше измерить один раз для if
      if ((millis() > soundTime) && ((secondSoundTime - soundTime) > 100) && ((secondSoundTime - soundTime) < 500))  {

        Serial.print("Motion detected!");
        start = !start;
        Serial.println(start);
        digitalWrite(13,start);
        digitalWrite(releOutputPin,start);
      }
      soundTime = millis();
      // We only want to print on the output change, not state
      soundState = HIGH;
    }
  } else {
    if (soundState == HIGH) {
      // we have just turned of
      Serial.println("Motion ended!");

      // We only want to print on the output change, not state
      soundState = LOW;
    }
  }
}

