/*
 это мой arduino web server, который считывает показатели и показывает их в локальной сети (пока)
 */

//импорт для web сервера
#include <SPI.h>
#include <Ethernet.h>

//импорт для датчика влажности и температуры
#include "DHT.h"
#define DHTPIN 2 // номер пина, к которому подсоединен датчик
// Раскомментируйте в соответствии с используемым датчиком
// Инициируем датчик
//DHT dht(DHTPIN, DHT22);
DHT dht(DHTPIN, DHT11);

//мак адрес
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

//ip адресс по которому будет доступен сервер
IPAddress ip(192, 168, 0, 20);

//порт для сервера
EthernetServer server(80);


// Реле модуль подключен к цифровому выводу 4
int Relay = 4;
boolean isOnRelay = false;

boolean receiving = false; //To keep track of whether we are getting data.

int clientCount = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
 
// start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

//запускаем датчик влажности и температуры
  dht.begin();  

//устанавливаем реле
    pinMode(Relay, OUTPUT);     
    pinMode(13, OUTPUT);
   // реле выключено
   //onOffRelay();
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
   boolean currentLineIsBlank = true;
   boolean sentHeader = false;
   while (client.connected())
   {
     if (client.available())
     {
       char c = client.read(); //Read from the incoming buffer

       if(receiving && c == ' ') receiving = false; //done receiving
       if(c == '?') receiving = true; //found arguments

       //This looks at the GET requests
       if(receiving)
       {
         if (c == 'l')
         {
            Serial.println("Execute lamp");
            onOffRelay();
           break;
         }
         //Add similarly formatted else if statements here
         //TO CONTROL ADDITIONAL THINGS

       }
    
       //Print out the response header and the HTML page
       if(!sentHeader)
       {
        
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          //client.println("<meta http-equiv='refresh' content='5'/>");
          client.println("<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
          client.println("<title>Данные с датчиков</title>");


          //кнопка обновления, чтоб не использовать обновления браузера
/*
        client.println("<form action='' method='get'>");
        client.println("<input type='submit' value='Обновить'/>");
        client.println("</form>");          
*/
          //выводим инфу

            client.print("Влажность: ");
            client.print(getHumidity());
            client.println(" % <br />");

            client.print("Температура: ");
            client.print(getTemperature());
            client.println(" °C<br />");

            client.print("Освещенность: ");
            client.print(getFotorezistorData());
            client.println("<br />");      

            //----------------------------------------------------------------------------------
            //работаем с реле
              client.println("<form action='' method='get'>");
              client.println("<input type='hidden' name='l'/>");
              Serial.print("Lamp now status: ");
              Serial.println(isOnRelay);
            if(isOnRelay){
              client.print("Лампочка <b>ВКЛЮЧЕНА</b>");
              client.println("<br />");
              client.println("<input type='submit' value='Выключить лампочку'/>");
            } else {
              client.print("Лампочка <b>ВЫКЛЮЧЕНА</b>");
              client.println("<br />");
              client.println("<input type='submit' value='Включить лампочку'/>");
            }
            client.println("</form>");
            //----------------------------------------------------------------------------------

          client.println("</html>");
     
          //Add additional forms forms for controlling more things here.
     
          sentHeader = true;
        }

        if (c == '\n' && currentLineIsBlank) break;

        if (c == '\n')
        {
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          currentLineIsBlank = false;
        }
      }
    }

    // give the web browser time to receive the data
    delay(5);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
    clientCount++;
    Serial.print("client count: ");
    Serial.println(clientCount);
  }
}


//Считываем влажность
float getHumidity(){
    float h = dht.readHumidity();
    // Проверка удачно прошло ли считывание.
    if (isnan(h)) {
      Serial.println("Не удается считать показания");
      return -5000;
    }
    return h;
}
  
//считываем температуру
float getTemperature(){
  float t = dht.readTemperature();
    if (isnan(t)) {
      Serial.println("Не удается считать показания");
      return -5000;
    }  
  return t;
}

//получаем освещенность
String getFotorezistorData(){
  /* Простой проверочный скетч для фоторерезистора.
  Подключите одну ногу фоторезистора к 5 В, вторую к пину Analog 0.
  После этого подключите контакт резистора на 10 кОм к земле, а второй к аналоговому пину Analog 0 */
  int photocellPin = 0; // сенсор и понижающий резистор на 10 кОм подключены к a0
  int photocellReading; // данные считываемые с аналогового пина  

  photocellReading = analogRead(photocellPin);
  String result;
   Serial.print(photocellReading); // аналоговые значения
  if (photocellReading < 100) {
    Serial.println(" - Dark");
    result = "темно";
  } else if (photocellReading < 200) {
    Serial.println(" - Dim");
    result = "тусклый";
  } else if (photocellReading < 500) {
    Serial.println(" - Light");
    result = "светло";
  } else if (photocellReading < 800) {
    Serial.println(" - Bright");
    result = "ярко";
  } else {
    Serial.println(" - Very bright");
    result = "очень ярко";
  }  
  return result;
}

void onOffRelay(){
    Serial.print("Lamp now: ");
    Serial.println(isOnRelay);
    isOnRelay = !isOnRelay;
  if (isOnRelay){
    digitalWrite(Relay, LOW);   // реле включено
    digitalWrite(13, HIGH);   
    Serial.println("Relay ON");
  } else {
    digitalWrite(Relay, HIGH);  // реле выключено
    digitalWrite(13, LOW);  
    Serial.println("Relay OFF");
  }
  Serial.print("Lamp end: ");
  Serial.println(isOnRelay);
}

