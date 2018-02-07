char text;


void setup() {
  text = "HTTP/1.1 200 OK" + 
  "Server: openresty" + 
  "Date: Sun, 04 Feb 2018 17:33:13 GMT" +
  "Content-Type: application/json; charset=utf-8" +
  "Content-Length: 443" +
  "Connection: close" +
  "X-Cache-Key: /data/2.5/weather?APPID=a84870f53a403e140f1be53017c9a3a0&id=542420" +
  "Access-Control-Allow-Origin: *" +
  "Access-Control-Allow-Credentials: true" +
  "Access-Control-Allow-Methods: GET, POST" +
  "" +
  "{\"coord\":{\"lon\":38.98,\"lat\":45.03},\"weather\":[{\"id\":800,\"main\":"Clear",\"description\":\"clear sky\",\"icon\":\"01n\"}],\"base\":\"stations\",\"main\":{\"temp\":286.15,\"pressure\":1008,\"humidity\":58,\"temp_min\":286.15,\"temp_max\":286.15},\"visibility\":10000,\"wind\":{\"speed\":2,\"deg\":240},\"clouds\":{\"all\":0},\"dt\":1517763600,\"sys\":{\"type\":1,\"id\":7295,\"message\":0.0076,\"country\":\"RU\",\"sunrise\":1517719186,\"sunset\":1517755014},\"id\":542420,\"name\":"Krasnodar","cod":200}" +
  
  Serial.begin(9600);
  Serial.println(text);
}

void loop() {
  // put your main code here, to run repeatedly:

}
