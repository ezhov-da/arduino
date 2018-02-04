#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "http://api.openweathermap.org";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /data/2.5/weather?id=542420&&APPID=a84870f53a403e140f1be53017c9a3a0  HTTP/1.1");
    client.println("Connection: close");
    client.println("Accept: text/html,application/xhtml+xm…plication/xml;q=0.9,*/*;q=0.8");
    client.println("Accept-Encoding: gzip, deflate");
    client.println("Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3");
    client.println("Cache-Control: max-age=0");
    client.println("Host: api.openweathermap.org");
    client.println("Upgrade-Insecure-Requests: 1");
    client.println("User-Agent: Mozilla/5.0 (Windows NT 10.0; …) Gecko/20100101 Firefox/57.0");
    client.println();

    Serial.println("executed send query");
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  } else {
    Serial.print("fuck");
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}

